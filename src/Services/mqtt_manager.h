#pragma once
#include <Arduino.h>

void initMQTT();
void handleMQTT();          // call every loop when WiFi connected
void connectMQTT();         // trigger connection attempt
void publishSensorData();   // publish current sensor readings
void mqttSetBroker(const String &host, int port);
void mqttSetCredentials(const String &user, const String &pass);
void mqttSetTopic(const String &topic);
