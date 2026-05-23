#include "mqtt_manager.h"
#include "../state.h"
#include "../Core/app.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_RECONNECT_INTERVAL 5000
#define MQTT_PUBLISH_INTERVAL   10000
#define MQTT_CLIENT_ID          "ESP_OS_Node"

static WiFiClient   wifiClient;
static PubSubClient mqttClient(wifiClient);
static unsigned long lastReconnectAttempt = 0;

// Incoming message callback
static void onMessage(char *topic, byte *payload, unsigned int length) {
  mqttLastPayload = "";
  for (unsigned int i = 0; i < length && i < 32; i++) {
    mqttLastPayload += (char)payload[i];
  }
}

void initMQTT() {
  mqttClient.setCallback(onMessage);
  mqttClient.setKeepAlive(30);
}

void mqttSetBroker(const String &host, int port) {
  mqttHost = host;
  mqttPort = port;
  mqttClient.setServer(mqttHost.c_str(), mqttPort);
}

void mqttSetCredentials(const String &user, const String &pass) {
  mqttUser = user;
  mqttPass = pass;
}

void mqttSetTopic(const String &topic) {
  mqttTopic = topic;
}

void connectMQTT() {
  mqttClient.setServer(mqttHost.c_str(), mqttPort);
  setPage(MQTT_CONNECTING);
  lastReconnectAttempt = 0;  // force immediate attempt
}

static bool tryConnect() {
  bool ok;
  if (mqttUser.length() > 0) {
    ok = mqttClient.connect(MQTT_CLIENT_ID,
                            mqttUser.c_str(),
                            mqttPass.c_str());
  } else {
    ok = mqttClient.connect(MQTT_CLIENT_ID);
  }
  if (ok) {
    mqttConnected = true;
    // Subscribe to command topic
    String cmdTopic = mqttTopic + "/cmd";
    mqttClient.subscribe(cmdTopic.c_str());
    if (page == MQTT_CONNECTING) setPage(MQTT_DASHBOARD);
  }
  return ok;
}

void publishSensorData() {
  if (!mqttClient.connected()) return;

  // Publish as simple key=value pairs on sub-topics
  String base = mqttTopic + "/";
  char buf[16];

  dtostrf(sensorTemp,     5, 1, buf); mqttClient.publish((base + "temp").c_str(),     buf);
  dtostrf(sensorHumidity, 5, 1, buf); mqttClient.publish((base + "humidity").c_str(), buf);
  dtostrf(sensorPressure, 7, 1, buf); mqttClient.publish((base + "pressure").c_str(), buf);

  mqttLastMsg = millis();
}

void handleMQTT() {
  if (!mqttClient.connected()) {
    mqttConnected = false;
    if (millis() - lastReconnectAttempt > MQTT_RECONNECT_INTERVAL) {
      lastReconnectAttempt = millis();
      tryConnect();
    }
  } else {
    mqttClient.loop();
    // Auto-publish sensor data on interval
    if (millis() - mqttLastMsg > MQTT_PUBLISH_INTERVAL) {
      publishSensorData();
    }
  }
}
