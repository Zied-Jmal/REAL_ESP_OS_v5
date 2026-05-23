#include "ui_mqtt.h"
#include "../display_cfg.h"
#include "../state.h"

void showMQTTMenu(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ MQTT / IoT ]="));
  d->print(F("Status: "));
  d->println(mqttConnected ? F("CONNECTED") : F("offline"));
  d->println(F("1 Dashboard"));
  d->println(F("2 Configure"));
  d->println(F("3 Publish now"));
  d->println(F("b=back"));
  d->display();
}

void showMQTTConfig(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ MQTT CONFIG ]="));
  d->print(F("Host: ")); d->println(mqttHost);
  d->print(F("Port: ")); d->println(mqttPort);
  d->print(F("Topic: ")); d->println(mqttTopic);
  d->println(F("Serial cmds:"));
  d->println(F("broker=h,port"));
  d->println(F("topic=t  connect"));
  d->display();
}

void showMQTTConnecting(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ MQTT ]="));
  d->println(F("Connecting..."));
  d->println(mqttHost);
  d->print(F(":")); d->println(mqttPort);
  d->display();
}

void showMQTTDashboard(Adafruit_SSD1306 *d) {
  dispReady(d);
  d->println(F("=[ MQTT LIVE ]="));
  d->print(F("Broker: ")); d->println(mqttHost);
  d->print(F("Topic:  ")); d->println(mqttTopic);
  d->print(F("Status: "));
  d->println(mqttConnected ? F("OK") : F("OFFLINE"));

  if (mqttLastMsg > 0) {
    d->print(F("Last tx: "));
    d->print((millis() - mqttLastMsg) / 1000);
    d->println(F("s ago"));
  }

  if (mqttLastPayload.length()) {
    d->print(F("Rx: ")); d->println(mqttLastPayload);
  }
  d->display();
}
