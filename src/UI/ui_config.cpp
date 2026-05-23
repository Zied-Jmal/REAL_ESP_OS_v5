#include "ui_config.h"
#include "../display_cfg.h"
#include "../state.h"
#include "../Services/config_manager.h"

void showConfigMenu(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ STORAGE ]="));
  d->println(F(""));
  d->print(F("SPIFFS: "));
  d->println(configLoaded ? F("loaded") : F("defaults"));
  d->println(F("1 View config"));
  d->println(F("2 Save config"));
  d->println(F("3 Reset config"));
  d->println(F("b=back"));
  d->display();
}

void showConfigView(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ CONFIG ]="));
  d->print(F("SSID: ")); d->println(ssid.length() ? ssid : F("(none)"));
  d->print(F("MQTT: ")); d->println(mqttHost);
  d->print(F(":")); d->println(mqttPort);
  d->print(F("Topic: ")); d->println(mqttTopic);
  d->println(F("b=back"));
  d->display();
}

void showConfigReset(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ RESET ]="));
  d->println(F("This will erase"));
  d->println(F("all saved config!"));
  d->println();
  d->println(F("Type 'yes' confirm"));
  d->println(F("Any key to cancel"));
  d->display();
}
