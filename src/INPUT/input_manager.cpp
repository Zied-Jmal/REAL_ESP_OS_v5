#include <Arduino.h>
#include "../Core/app.h"
#include "../Services/wifi_manager.h"
#include "../Services/mqtt_manager.h"
#include "../Services/config_manager.h"
#include "../Services/ota_manager.h"
#include "../state.h"
#include "input_manager.h"
#include <ESP8266WiFi.h>

static void handleCommand(const String &cmd);

void initInput() {
  Serial.begin(115200);
  Serial.println(F("\r\n[ESP-OS v4] Ready. Type 'h' for home, 'm' for menu."));
}

void handleInput() {
  if (!Serial.available()) return;
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  if (cmd.length() == 0) return;
  Serial.print(F("> ")); Serial.println(cmd);
  handleCommand(cmd);
}

// ── Helper: print usage hint to serial ───────────────────────────────────────
static void hint(const char *msg) {
  Serial.println(msg);
}

static void handleCommand(const String &cmd) {

  // ── Global shortcuts ──────────────────────────────────────────────────────
  if (cmd == "h") { setPage(HOME);   return; }
  if (cmd == "m") { setPage(MENU);   return; }
  if (cmd == "b") {
    // "back" — go to parent menu based on current page
    Page cur = getPage();
    if (cur >= SENSOR_TEMP && cur <= SENSOR_ALL)        setPage(SENSOR_MENU);
    else if (cur >= MQTT_CONFIG && cur <= MQTT_PUBLISH)  setPage(MQTT_MENU);
    else if (cur == NET_SCANNER || cur == NET_MESH)      setPage(NET_MENU);
    else if (cur == CONFIG_VIEW || cur == CONFIG_RESET)  setPage(CONFIG_MENU);
    else if (cur == OTA_ACTIVE)                          setPage(OTA_MENU);
    else                                                 setPage(MENU);
    return;
  }

  Page cur = getPage();

  // ── MAIN MENU ─────────────────────────────────────────────────────────────
  if (cur == MENU) {
    if      (cmd == "1") setPage(WIFI_SETUP);
    else if (cmd == "2") setPage(DASHBOARD);
    else if (cmd == "3") setPage(HOTSPOT);
    else if (cmd == "4") setPage(SENSOR_MENU);
    else if (cmd == "5") setPage(MQTT_MENU);
    else if (cmd == "6") setPage(NET_MENU);
    else if (cmd == "7") setPage(CONFIG_MENU);
    else if (cmd == "8") setPage(OTA_MENU);
    else if (cmd == "9") setPage(SYSTEM_INFO);
    return;
  }

  // ── WIFI SETUP ───────────────────────────────────────────────────────────
  if (cur == WIFI_SETUP) {
    int sep = cmd.indexOf(',');
    if (sep > 0) {
      String s = cmd.substring(0, sep);  s.trim();
      String p = cmd.substring(sep + 1); p.trim();
      if (s.length() && p.length()) {
        startWiFi(s, p);
      } else {
        hint("[wifi] Bad format. Use: ssid,password");
      }
    } else {
      hint("[wifi] Format: ssid,password");
    }
    return;
  }

  // ── SENSOR MENU ──────────────────────────────────────────────────────────
  if (cur == SENSOR_MENU) {
    if      (cmd == "1") setPage(SENSOR_TEMP);
    else if (cmd == "2") setPage(SENSOR_HUMIDITY);
    else if (cmd == "3") setPage(SENSOR_PRESSURE);
    else if (cmd == "4") setPage(SENSOR_ALL);
    return;
  }

  // ── MQTT MENU ────────────────────────────────────────────────────────────
  if (cur == MQTT_MENU) {
    if      (cmd == "1") setPage(MQTT_DASHBOARD);
    else if (cmd == "2") setPage(MQTT_CONFIG);
    else if (cmd == "3") { publishSensorData(); hint("[mqtt] Published."); }
    return;
  }

  // ── MQTT CONFIG: set broker=host,port  user=u,p  topic=t ─────────────────
  if (cur == MQTT_CONFIG) {
    if (cmd.startsWith("broker=")) {
      String val = cmd.substring(7);
      int sep = val.indexOf(',');
      if (sep > 0) {
        mqttSetBroker(val.substring(0, sep), val.substring(sep + 1).toInt());
        hint("[mqtt] Broker set");
      } else {
        mqttSetBroker(val, 1883);
        hint("[mqtt] Broker set (port 1883)");
      }
    } else if (cmd.startsWith("user=")) {
      String val = cmd.substring(5);
      int sep = val.indexOf(',');
      if (sep > 0) {
        mqttSetCredentials(val.substring(0, sep), val.substring(sep + 1));
        hint("[mqtt] Credentials set");
      }
    } else if (cmd.startsWith("topic=")) {
      mqttSetTopic(cmd.substring(6));
      hint("[mqtt] Topic set");
    } else if (cmd == "connect") {
      connectMQTT();
    } else {
      hint("[mqtt] Commands: broker=host,port | user=u,p | topic=t | connect");
    }
    return;
  }

  // ── NET MENU ─────────────────────────────────────────────────────────────
  if (cur == NET_MENU) {
    if      (cmd == "1") setPage(NET_SCANNER);
    else if (cmd == "2") setPage(NET_MESH);
    return;
  }

  // ── NET SCANNER: scroll through results ──────────────────────────────────
  if (cur == NET_SCANNER) {
    if (cmd == "n" && scanOffset + 3 < scanCount) scanOffset++;
    if (cmd == "p" && scanOffset > 0)             scanOffset--;
    if (cmd == "r") { setPage(NET_SCANNER); }     // re-scan
    return;
  }

  // ── CONFIG MENU ──────────────────────────────────────────────────────────
  if (cur == CONFIG_MENU) {
    if      (cmd == "1") setPage(CONFIG_VIEW);
    else if (cmd == "2") { saveConfig(); hint("[config] Saved."); }
    else if (cmd == "3") setPage(CONFIG_RESET);
    return;
  }

  // ── CONFIG RESET confirm ─────────────────────────────────────────────────
  if (cur == CONFIG_RESET) {
    if (cmd == "yes") { resetConfig(); setPage(HOME); }
    else              { setPage(CONFIG_MENU); }
    return;
  }

  // ── OTA MENU ─────────────────────────────────────────────────────────────
  if (cur == OTA_MENU) {
    if (cmd == "1") {
      if (WiFi.status() != WL_CONNECTED) {
        hint("[ota] Connect to WiFi first");
      } else {
        startOTA();
        setPage(OTA_ACTIVE);
      }
    } else if (cmd == "2") {
      stopOTA();
      setPage(MENU);
    }
    return;
  }
}
