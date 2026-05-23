#include "app.h"
#include "../state.h"
#include "../Services/mqtt_manager.h"
#include "../Services/sensor_manager.h"
#include "../Services/ota_manager.h"
#include <ESP8266WiFi.h>

#define WIFI_TIMEOUT_MS 12000

void setPage(Page p) {
  // Teardown on leaving certain pages
  if (page == HOTSPOT && p != HOTSPOT) {
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);
    hotspotActive = false;
  }
  if (page == OTA_ACTIVE && p != OTA_ACTIVE) {
    otaActive   = false;
    otaProgress = 0;
  }
  // Trigger scan when entering scanner
  if (p == NET_SCANNER) {
    scanDone   = false;
    scanCount  = 0;
    scanOffset = 0;
    WiFi.scanNetworksAsync([](int n) {
      scanCount = n;
      scanDone  = true;
    });
  }
  page = p;
}

Page getPage() { return page; }

void handleAppLogic() {
  // WiFi connection timeout
  if (page == CONNECTING) {
    if (WiFi.status() == WL_CONNECTED) {
      setPage(DASHBOARD);
      return;
    }
    if (millis() - wifiStart > WIFI_TIMEOUT_MS) {
      setPage(HOME);
      return;
    }
  }

  // Always tick services when WiFi is up
  if (WiFi.status() == WL_CONNECTED) {
    handleMQTT();
  }

  // Sensors update regardless of WiFi
  updateSensors();

  // OTA tick
  if (otaActive) {
    handleOTA();
  }
}
