#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoOTA.h>

#include "display_cfg.h"
#include "state.h"
#include "Core/app.h"
#include "INPUT/input_manager.h"
#include "Services/sensor_manager.h"
#include "Services/mqtt_manager.h"
#include "Services/config_manager.h"
#include "Services/ota_manager.h"

#include "UI/ui_home.h"
#include "UI/ui_menu.h"
#include "UI/ui_wifi.h"
#include "UI/ui_status.h"
#include "UI/ui_hotspot.h"
#include "UI/ui_system.h"
#include "UI/ui_sensors.h"
#include "UI/ui_mqtt.h"
#include "UI/ui_network.h"
#include "UI/ui_config.h"
#include "UI/ui_ota.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static void halt(const char *msg) {
  Serial.println(msg);
  pinMode(LED_BUILTIN, OUTPUT);
  while (true) {
    digitalWrite(LED_BUILTIN, LOW);  delay(150);
    digitalWrite(LED_BUILTIN, HIGH); delay(150);
  }
}

void setup() {
  initInput();   // Serial.begin inside here

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    halt("[FATAL] SSD1306 not found");
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Splash
  display.clearDisplay();
  display.setCursor(14, 10);
  display.setTextSize(2);
  display.println(F("ESP-OS"));
  display.setTextSize(1);
  display.setCursor(28, 36);
  display.println(F("v4  booting..."));
  display.display();
  delay(1500);

  // Init all services
  initConfig();    // SPIFFS — loads saved ssid/mqtt settings
  initSensors();
  initMQTT();
  initOTA();

  // Auto-connect if config was saved
  if (ssid.length() > 0) {
    Serial.println(F("[boot] Auto-connecting WiFi from config..."));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());
    wifiStart = millis();
    setPage(CONNECTING);
  }
}

void loop() {
  handleInput();
  handleAppLogic();

  switch (getPage()) {
    // Core
    case HOME:           showHome(&display);           break;
    case MENU:           showMenu(&display);           break;

    // WiFi
    case WIFI_SETUP:     showWiFi(&display);           break;
    case CONNECTING:     showWiFiConnecting(&display); break;

    // Main screens
    case DASHBOARD:      showStatus(&display);         break;
    case HOTSPOT:        showHotspot(&display);        break;
    case SYSTEM_INFO:    showSystem(&display);         break;

    // Sensors
    case SENSOR_MENU:    showSensorMenu(&display);     break;
    case SENSOR_TEMP:    showSensorTemp(&display);     break;
    case SENSOR_HUMIDITY:showSensorHumidity(&display); break;
    case SENSOR_PRESSURE:showSensorPressure(&display); break;
    case SENSOR_ALL:     showSensorAll(&display);      break;

    // MQTT
    case MQTT_MENU:      showMQTTMenu(&display);       break;
    case MQTT_CONFIG:    showMQTTConfig(&display);     break;
    case MQTT_CONNECTING:showMQTTConnecting(&display); break;
    case MQTT_DASHBOARD: showMQTTDashboard(&display);  break;

    // Network
    case NET_MENU:       showNetMenu(&display);        break;
    case NET_SCANNER:    showNetScanner(&display);     break;
    case NET_MESH:       showNetMesh(&display);        break;

    // Config / Storage
    case CONFIG_MENU:    showConfigMenu(&display);     break;
    case CONFIG_VIEW:    showConfigView(&display);     break;
    case CONFIG_RESET:   showConfigReset(&display);    break;

    // OTA
    case OTA_MENU:       showOTAMenu(&display);        break;
    case OTA_ACTIVE:     showOTAActive(&display);      break;

    default: break;
  }

  delay(200);
}
