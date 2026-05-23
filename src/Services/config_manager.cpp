#include "config_manager.h"
#include "../state.h"
#include <FS.h>   // SPIFFS

#define CONFIG_FILE "/config.txt"

// ── Simple key=value parser ───────────────────────────────────────────────────
static String getValue(const String &data, const String &key) {
  int start = data.indexOf(key + "=");
  if (start < 0) return "";
  start += key.length() + 1;
  int end = data.indexOf('\n', start);
  if (end < 0) end = data.length();
  String val = data.substring(start, end);
  val.trim();
  return val;
}

void initConfig() {
  if (!SPIFFS.begin()) {
    Serial.println(F("[config] SPIFFS mount failed"));
    return;
  }
  loadConfig();
}

void loadConfig() {
  if (!SPIFFS.exists(CONFIG_FILE)) {
    Serial.println(F("[config] No config file found, using defaults"));
    configLoaded = false;
    return;
  }

  File f = SPIFFS.open(CONFIG_FILE, "r");
  if (!f) return;

  String data = f.readString();
  f.close();

  String v;
  v = getValue(data, "ssid");      if (v.length()) ssid = v;
  v = getValue(data, "pass");      if (v.length()) pass = v;
  v = getValue(data, "mqttHost");  if (v.length()) mqttHost = v;
  v = getValue(data, "mqttPort");  if (v.length()) mqttPort = v.toInt();
  v = getValue(data, "mqttUser");  if (v.length()) mqttUser = v;
  v = getValue(data, "mqttPass");  if (v.length()) mqttPass = v;
  v = getValue(data, "mqttTopic"); if (v.length()) mqttTopic = v;

  configLoaded = true;
  Serial.println(F("[config] Loaded from SPIFFS"));
}

void saveConfig() {
  File f = SPIFFS.open(CONFIG_FILE, "w");
  if (!f) {
    Serial.println(F("[config] Failed to open for write"));
    return;
  }

  f.println("ssid="      + ssid);
  f.println("pass="      + pass);
  f.println("mqttHost="  + mqttHost);
  f.println("mqttPort="  + String(mqttPort));
  f.println("mqttUser="  + mqttUser);
  f.println("mqttPass="  + mqttPass);
  f.println("mqttTopic=" + mqttTopic);

  f.close();
  configLoaded = true;
  Serial.println(F("[config] Saved to SPIFFS"));
}

void resetConfig() {
  SPIFFS.remove(CONFIG_FILE);
  ssid = pass = mqttUser = mqttPass = "";
  mqttHost  = "broker.hivemq.com";
  mqttPort  = 1883;
  mqttTopic = "esp/os/data";
  configLoaded = false;
  Serial.println(F("[config] Reset to defaults"));
}

String getConfigSummary() {
  String s = "";
  s += "SSID: "  + (ssid.length() ? ssid : "(none)") + "\n";
  s += "MQTT: "  + mqttHost + "\n";
  s += "Port: "  + String(mqttPort) + "\n";
  s += "Topic: " + mqttTopic + "\n";
  s += "User: "  + (mqttUser.length() ? mqttUser : "(none)") + "\n";
  return s;
}
