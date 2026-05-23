#pragma once
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C
#define OLED_SDA        14
#define OLED_SCL        12

// Reset cursor, white text, size 1 — call at start of every draw function
inline void dispReady(Adafruit_SSD1306 *d) {
  d->clearDisplay();
  d->setTextSize(1);
  d->setTextColor(SSD1306_WHITE);
  d->setCursor(0, 0);
}

// Draw a full-width horizontal rule at current Y (uses drawFastHLine)
inline void dispHR(Adafruit_SSD1306 *d) {
  int y = d->getCursorY();
  d->drawFastHLine(0, y, SCREEN_WIDTH, SSD1306_WHITE);
  d->setCursor(0, y + 2);
}
