#include "ui_hotspot.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

#define AP_SSID "ESP_OS_AP"
#define AP_PASS "12345678"

void showHotspot(Adafruit_SSD1306 *d) {
  if (!hotspotActive) {
    WiFi.disconnect(true);
    delay(100);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
    hotspotActive = true;
  }

  dispReady(d);
  d->println(F("=[ HOTSPOT ]="));
  d->println(F("SSID:"));
  d->println(F("  " AP_SSID));
  d->println(F("PASS: " AP_PASS));
  d->print(F("IP: ")); d->println(WiFi.softAPIP());
  d->print(F("Clients: ")); d->println(WiFi.softAPgetStationNum());
  d->display();
}
