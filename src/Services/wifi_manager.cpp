#include "wifi_manager.h"
#include "../state.h"
#include "../Core/app.h"
#include <ESP8266WiFi.h>

void startWiFi(const String &s, const String &p) {
  ssid = s;
  pass = p;
  WiFi.disconnect(true);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());
  wifiStart = millis();
  setPage(CONNECTING);
}
