#include "sensor_manager.h"
#include "../state.h"
#include <Arduino.h>

#define SENSOR_INTERVAL_MS 3000

// Simulates realistic slow drift around baseline values
static float drift(float current, float baseline, float maxStep, float maxDev) {
  float step = ((float)random(-100, 100) / 100.0f) * maxStep;
  float next = current + step;
  // Nudge back toward baseline if drifting too far
  if (next > baseline + maxDev) next -= maxStep * 2;
  if (next < baseline - maxDev) next += maxStep * 2;
  return next;
}

void initSensors() {
  randomSeed(analogRead(A0));
  sensorTemp     = 22.5f;
  sensorHumidity = 55.0f;
  sensorPressure = 1013.0f;
}

void updateSensors() {
  if (millis() - sensorLastUpdate < SENSOR_INTERVAL_MS) return;
  sensorLastUpdate = millis();

  sensorTemp     = drift(sensorTemp,     22.5f,  0.3f, 5.0f);
  sensorHumidity = drift(sensorHumidity, 55.0f,  0.5f, 15.0f);
  sensorPressure = drift(sensorPressure, 1013.0f, 0.2f, 8.0f);
}
