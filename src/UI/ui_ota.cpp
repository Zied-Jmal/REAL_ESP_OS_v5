#include "ui_ota.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

void showOTAMenu(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ OTA UPDATE ]="));
  d->print(F("WiFi: "));
  d->println(WiFi.status() == WL_CONNECTED ? F("ready") : F("! need WiFi"));
  d->println(F("Host: ESP-OS"));
  d->println(F("Pass: esp1234"));
  d->println(F("1 Start OTA"));
  d->println(F("2 Stop / b=back"));
  d->display();
}

void showOTAActive(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ OTA ACTIVE ]="));
  d->println(WiFi.localIP());
  d->println(F("Waiting for upload"));
  d->println(F("via Arduino IDE"));
  d->println(F("or pio run -t upload"));
  d->println();

  // Progress bar (only shows once upload starts)
  if (otaProgress > 0) {
    int bar = map(otaProgress, 0, 100, 0, SCREEN_WIDTH - 2);
    int y = d->getCursorY();
    d->drawRect(0, y, SCREEN_WIDTH, 6, SSD1306_WHITE);
    d->fillRect(1, y + 1, bar, 4, SSD1306_WHITE);
    d->setCursor(0, y + 8);
    d->print(otaProgress); d->println(F("%"));
  }

  d->display();
}
