#include "ui_system.h"
#include "../display_cfg.h"

void showSystem(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ SYSTEM INFO ]="));
  d->print(F("CPU:   ")); d->print(ESP.getCpuFreqMHz()); d->println(F(" MHz"));
  d->print(F("Flash: ")); d->print(ESP.getFlashChipSize() / 1024); d->println(F(" KB"));
  d->print(F("Heap:  ")); d->print(ESP.getFreeHeap()); d->println(F(" B"));
  d->print(F("Chip:  ")); d->println(ESP.getChipId(), HEX);
  d->print(F("SDK:   ")); d->println(ESP.getSdkVersion());
  d->display();
}
