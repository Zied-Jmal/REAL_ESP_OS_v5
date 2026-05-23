#include "ui_wifi.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

void showWiFi(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ WIFI SETUP ]="));
  d->println(F("Serial format:"));
  d->println(F("  ssid,password"));
  d->println();
  d->println(F("b=back  h=home"));
  d->display();
}

void showWiFiConnecting(Adafruit_SSD1306 *d) {
  dispReady(d);

  if (WiFi.status() == WL_CONNECTED) {
    d->println(F("  CONNECTED!"));
    d->println();
    d->println(WiFi.localIP());
    d->display();
    return;
  }

  unsigned long elapsed = millis() - wifiStart;
  int bar = map(constrain(elapsed, 0, 12000), 0, 12000, 0, 18);

  d->println(F("CONNECTING..."));
  d->println(ssid);
  d->println();
  d->print(F("["));
  for (int i = 0; i < 18; i++) d->print(i < bar ? '=' : '-');
  d->println(F("]"));
  d->print(F("status: ")); d->println(WiFi.status());
  d->display();
}
