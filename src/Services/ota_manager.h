#pragma once

void initOTA();
void handleOTA();     // call in loop when otaActive = true
void startOTA();      // arm the OTA listener
void stopOTA();
