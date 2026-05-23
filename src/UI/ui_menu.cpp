#include "ui_menu.h"
#include "../display_cfg.h"

void showMenu(Adafruit_SSD1306 *d) {
  dispReady(d);

  d->println(F("=[ MAIN MENU ]="));
  d->println(F("               "));
  d->println(F("1 WiFi    6 Config"));
  d->println(F("2 Dash    7 Storage"));
  d->println(F("3 Hotspot 8 OTA"));
  d->println(F("4 Sensors 9 System"));
  d->println(F("5 MQTT"));
  d->println();
  d->println(F("h=home  b=back"));
  d->display();
}
