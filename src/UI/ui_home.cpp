#include "ui_home.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

void showHome(Adafruit_SSD1306 *d) {
  dispReady(d);

  d->setTextSize(1);
  d->println(F("  ESP8266  OS  v4"));
  d->println(F(""));

  dispHR(d);

  if (WiFi.status() == WL_CONNECTED) {
    d->println(F("WiFi: CONNECTED"));
    d->println(WiFi.localIP());
    d->print(F("RSSI: ")); d->print(WiFi.RSSI()); d->println(F(" dBm"));
  } else {
    d->println(F("WiFi: OFFLINE"));
  }

  // Show MQTT status on home
  d->print(F("MQTT: "));
  d->println(mqttConnected ? F("ON") : F("OFF"));

  d->println(F("m=menu  h=home"));
  d->display();
}
