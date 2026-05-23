#include "state.h"

// Core
Page          page          = HOME;
String        ssid          = "";
String        pass          = "";
unsigned long wifiStart     = 0;
bool          hotspotActive = false;

// MQTT
String        mqttHost        = "broker.hivemq.com";
int           mqttPort        = 1883;
String        mqttUser        = "";
String        mqttPass        = "";
String        mqttTopic       = "esp/os/data";
bool          mqttConnected   = false;
unsigned long mqttLastMsg     = 0;
String        mqttLastPayload = "";

// Sensors
float         sensorTemp        = 0.0f;
float         sensorHumidity    = 0.0f;
float         sensorPressure    = 0.0f;
unsigned long sensorLastUpdate  = 0;

// Network scanner
int           scanCount  = 0;
bool          scanDone   = false;
int           scanOffset = 0;

// OTA
bool          otaActive   = false;
int           otaProgress = 0;

// Config
bool          configLoaded = false;
