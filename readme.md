#RGB LED Clock
RGB LED clock made with WS2812 leds.
Features:
- Ambient light sensor for automatic dimming
- Uses NTP to get the current time (thanks to [NTPClient libary](https://github.com/arduino-libraries/NTPClient))
- Support for timezones and day light saving time (thanks to [Timezone libary](https://github.com/JChristensen/Timezone))
- Highlight every quarter hour

Libarys:
- FastLED
- WS2812DisplayDriver
- NTPClient
- Timezone
- ESP8266WiFi (part of ESP8266 core)
- WiFiUdp (part of ESP8266 core)