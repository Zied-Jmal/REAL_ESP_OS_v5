#include "ui_status.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

void showStatus(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ DASHBOARD ]="));

  if (WiFi.status() == WL_CONNECTED) {
    d->print(F("IP:   ")); d->println(WiFi.localIP());
    d->print(F("RSSI: ")); d->print(WiFi.RSSI()); d->println(F(" dBm"));
  } else {
    d->println(F("WiFi: OFFLINE"));
  }

  d->print(F("Heap: "));
  d->print(ESP.getFreeHeap() / 1024); d->println(F(" KB"));

  unsigned long s = millis() / 1000;
  d->print(F("Up:   "));
  d->print(s / 3600); d->print(F("h "));
  d->print((s % 3600) / 60); d->println(F("m"));

  d->print(F("MQTT: "));
  d->println(mqttConnected ? F("connected") : F("offline"));

  d->display();
}
