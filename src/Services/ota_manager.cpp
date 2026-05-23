#include "ota_manager.h"
#include "../state.h"
#include <ArduinoOTA.h>

void initOTA() {
  ArduinoOTA.setHostname("ESP-OS");
  ArduinoOTA.setPassword("esp1234");   // change as needed

  ArduinoOTA.onStart([]() {
    otaActive   = true;
    otaProgress = 0;
    Serial.println(F("[OTA] Start"));
  });

  ArduinoOTA.onEnd([]() {
    otaProgress = 100;
    Serial.println(F("[OTA] Done"));
  });

  ArduinoOTA.onProgress([](unsigned int done, unsigned int total) {
    otaProgress = (done * 100) / total;
  });

  ArduinoOTA.onError([](ota_error_t err) {
    Serial.print(F("[OTA] Error: "));
    Serial.println(err);
    otaActive = false;
  });

  // Don't begin here — call startOTA() explicitly
}

void startOTA() {
  ArduinoOTA.begin();
  otaActive   = true;
  otaProgress = 0;
  Serial.println(F("[OTA] Listening on port 8266"));
}

void stopOTA() {
  otaActive = false;
  Serial.println(F("[OTA] Stopped"));
}

void handleOTA() {
  ArduinoOTA.handle();
}
