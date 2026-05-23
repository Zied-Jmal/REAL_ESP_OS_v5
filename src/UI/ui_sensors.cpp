#include "ui_sensors.h"
#include "../display_cfg.h"
#include "../state.h"

// Draws a simple horizontal bar on the OLED
static void drawBar(Adafruit_SSD1306 *d, float value, float minVal, float maxVal) {
  int barW = (int)map((long)value, (long)minVal, (long)maxVal, 0, SCREEN_WIDTH - 2);
  barW = constrain(barW, 0, SCREEN_WIDTH - 2);
  int y = d->getCursorY();
  d->drawRect(0, y, SCREEN_WIDTH, 6, SSD1306_WHITE);
  d->fillRect(1, y + 1, barW, 4, SSD1306_WHITE);
  d->setCursor(0, y + 8);
}

void showSensorMenu(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ SENSORS ]="));
  d->println(F("1 Temperature"));
  d->println(F("2 Humidity"));
  d->println(F("3 Pressure"));
  d->println(F("4 All readings"));
  d->println(F("b=back"));
  d->display();
}

void showSensorTemp(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ TEMPERATURE ]="));
  d->println(F("[simulated]"));
  d->print(F("  "));
  d->print(sensorTemp, 1);
  d->println(F(" C"));
  d->println();
  drawBar(d, sensorTemp, 0.0f, 50.0f);
  d->println(F("range: 0 - 50 C"));
  d->println(F("b=back"));
  d->display();
}

void showSensorHumidity(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ HUMIDITY ]="));
  d->println(F("[simulated]"));
  d->print(F("  "));
  d->print(sensorHumidity, 1);
  d->println(F(" %RH"));
  d->println();
  drawBar(d, sensorHumidity, 0.0f, 100.0f);
  d->println(F("range: 0 - 100 %"));
  d->println(F("b=back"));
  d->display();
}

void showSensorPressure(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ PRESSURE ]="));
  d->println(F("[simulated]"));
  d->print(F("  "));
  d->print(sensorPressure, 1);
  d->println(F(" hPa"));
  d->println();
  drawBar(d, sensorPressure, 950.0f, 1080.0f);
  d->println(F("range: 950-1080 hPa"));
  d->println(F("b=back"));
  d->display();
}

void showSensorAll(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ ALL SENSORS ]="));
  d->print(F("Temp:  ")); d->print(sensorTemp, 1);     d->println(F(" C"));
  d->print(F("Hum:   ")); d->print(sensorHumidity, 1); d->println(F(" %"));
  d->print(F("Press: ")); d->print(sensorPressure, 1); d->println(F(" hPa"));
  d->println(F("[simulated data]"));
  d->println(F("b=back"));
  d->display();
}
