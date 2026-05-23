#pragma once
#include <Arduino.h>

void initConfig();          // mount SPIFFS, load config
void saveConfig();          // write current state to /config.txt
void loadConfig();          // read /config.txt into state vars
void resetConfig();         // delete /config.txt, reset to defaults
String getConfigSummary();  // returns multi-line string for display
