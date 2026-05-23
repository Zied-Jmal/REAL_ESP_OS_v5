#include "ui_network.h"
#include "../display_cfg.h"
#include "../state.h"
#include <ESP8266WiFi.h>

void showNetMenu(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ NETWORK ]="));
  d->println(F("1 WiFi Scanner"));
  d->println(F("2 Mesh / Nodes"));
  d->println();
  d->println(F("b=back"));
  d->display();
}

void showNetScanner(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ SCANNER ]="));

  if (!scanDone) {
    d->println(F("Scanning..."));
    d->display();
    return;
  }

  if (scanCount == 0) {
    d->println(F("No networks found"));
    d->println(F("r=rescan  b=back"));
    d->display();
    return;
  }

  d->print(F("Found: ")); d->print(scanCount);
  d->print(F("  [")); d->print(scanOffset + 1); d->print(F("-"));
  d->print(min(scanOffset + 3, scanCount)); d->println(F("]"));

  // Show 3 results at a time, scrollable with n/p
  for (int i = scanOffset; i < min(scanOffset + 3, scanCount); i++) {
    String name = WiFi.SSID(i);
    if (name.length() > 13) name = name.substring(0, 12) + "~";
    d->print(name);
    d->print(F(" "));
    d->print(WiFi.RSSI(i));
    d->println(WiFi.encryptionType(i) == ENC_TYPE_NONE ? F(" open") : F(" *"));
  }

  d->println(F("n=next p=prev r=scan"));
  d->display();
}

void showNetMesh(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ MESH/NODES ]="));
  d->println(F("Node ID:"));
  d->println(ESP.getChipId(), HEX);
  d->println(F("Role: standalone"));
  d->println(F("Peers: 0"));
  d->println(F("(ESP-NOW ready)"));
  d->println(F("b=back"));
  d->display();
}
