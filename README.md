# ESP8266 OS — v4

A mini OS for ESP8266 with 0.96" SSD1306 OLED.

---

## Hardware

| OLED pin | ESP8266 (NodeMCU) |
|----------|-------------------|
| SDA      | D5 (GPIO 14)      |
| SCL      | D6 (GPIO 12)      |
| VCC      | 3.3 V             |
| GND      | GND               |

Change `OLED_SDA` / `OLED_SCL` in `display_cfg.h` if your wiring differs.

---

## Build & Flash

```bash
pio run --target upload
pio device monitor      # 115200 baud
```

---

## Serial Command Reference

### Global (work from any screen)
| Command | Effect |
|---------|--------|
| `h`     | Home   |
| `m`     | Menu   |
| `b`     | Back to parent menu |

### Main Menu
| Key | Screen |
|-----|--------|
| `1` | WiFi Setup |
| `2` | Dashboard |
| `3` | Hotspot |
| `4` | Sensors |
| `5` | MQTT / IoT |
| `6` | Network |
| `7` | Storage (SPIFFS) |
| `8` | OTA Update |
| `9` | System Info |

### WiFi Setup
```
ssid,password         Connect to AP
```

### Sensors
| Key | Screen |
|-----|--------|
| `1` | Temperature |
| `2` | Humidity |
| `3` | Pressure |
| `4` | All readings |

### MQTT
| Key / Command | Effect |
|---------------|--------|
| `1` | MQTT Dashboard |
| `2` | Configure |
| `3` | Publish sensor data now |
| `broker=host,port` | Set broker (from Config screen) |
| `user=username,password` | Set credentials |
| `topic=my/topic` | Set publish topic |
| `connect` | Connect to broker |

Default broker: `broker.hivemq.com:1883` (public, no auth needed)

### Network
| Key | Effect |
|-----|--------|
| `1` | WiFi Scanner |
| `2` | Mesh / Nodes |
| `n` | Next results (scanner) |
| `p` | Previous results |
| `r` | Re-scan |

### Storage
| Key | Effect |
|-----|--------|
| `1` | View current config |
| `2` | Save config to SPIFFS |
| `3` | Reset config (prompts `yes` to confirm) |

### OTA
| Key | Effect |
|-----|--------|
| `1` | Start OTA listener |
| `2` | Stop OTA |

OTA hostname: `ESP-OS`, password: `esp1234`
Flash via: Arduino IDE → Tools → Port (network) or `pio run -t upload --upload-port <IP>`

---

## Features Added in v4

| Feature | Details |
|---------|---------|
| Sensor Menu | Simulated temp/humidity/pressure with bar graphs, realistic drift |
| MQTT / IoT | PubSubClient, auto-reconnect, publish sensor data every 10s, receive commands |
| Network Scanner | Async WiFi scan, scrollable results (n/p), encryption indicator |
| Mesh / Nodes | ESP-NOW ready scaffold, shows node ID |
| SPIFFS Storage | Save/load ssid, mqtt config; auto-connect on boot |
| OTA Update | ArduinoOTA, progress bar on OLED, password protected |
| Global `b` key | Context-aware back navigation |
| Auto-connect | Loads saved WiFi creds from SPIFFS on boot |
| MQTT Status | Shown on Home and Dashboard screens |
