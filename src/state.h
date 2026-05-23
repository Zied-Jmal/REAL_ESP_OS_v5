#pragma once
#include <Arduino.h>

// ── Pages ─────────────────────────────────────────────────────────────────────
enum Page {
  // Core
  HOME,
  MENU,

  // WiFi
  WIFI_SETUP,
  CONNECTING,

  // Main menu items
  DASHBOARD,
  HOTSPOT,
  SYSTEM_INFO,

  // Sensors
  SENSOR_MENU,
  SENSOR_TEMP,
  SENSOR_HUMIDITY,
  SENSOR_PRESSURE,
  SENSOR_ALL,

  // MQTT / IoT
  MQTT_MENU,
  MQTT_CONFIG,
  MQTT_CONNECTING,
  MQTT_DASHBOARD,
  MQTT_PUBLISH,

  // Network
  NET_MENU,
  NET_SCANNER,
  NET_MESH,

  // Storage / Config
  CONFIG_MENU,
  CONFIG_VIEW,
  CONFIG_RESET,

  // OTA
  OTA_MENU,
  OTA_ACTIVE,
};

// ── WiFi ──────────────────────────────────────────────────────────────────────
extern Page          page;
extern String        ssid;
extern String        pass;
extern unsigned long wifiStart;
extern bool          hotspotActive;

// ── MQTT ──────────────────────────────────────────────────────────────────────
extern String        mqttHost;
extern int           mqttPort;
extern String        mqttUser;
extern String        mqttPass;
extern String        mqttTopic;
extern bool          mqttConnected;
extern unsigned long mqttLastMsg;
extern String        mqttLastPayload;

// ── Sensors (simulated) ───────────────────────────────────────────────────────
extern float         sensorTemp;
extern float         sensorHumidity;
extern float         sensorPressure;
extern unsigned long sensorLastUpdate;

// ── Network scanner ───────────────────────────────────────────────────────────
extern int           scanCount;
extern bool          scanDone;
extern int           scanOffset;       // scroll offset for results

// ── OTA ───────────────────────────────────────────────────────────────────────
extern bool          otaActive;
extern int           otaProgress;

// ── Config (SPIFFS) ───────────────────────────────────────────────────────────
extern bool          configLoaded;
