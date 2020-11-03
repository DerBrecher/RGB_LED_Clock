# RGB LED Clock
RGB LED clock made with WS2812 leds.
Features:
- Ambient light sensor for automatic dimming
- Uses NTP to get the current time (thanks to [NTPClient libary](https://github.com/arduino-libraries/NTPClient))
- Support for timezones and day light saving time (thanks to [Timezone libary](https://github.com/JChristensen/Timezone))
- Highlight every quarter hour

Libarys:
- ([FastLED](https://github.com/FastLED/FastLED)) now using NeoPixelBus
- [NeoPixelBus](https://github.com/Makuna/NeoPixelBus)
- [WS2812DisplayDriver](https://github.com/DerBrecher/RGB_LED_Display_Driver)
- [NTPClient](https://github.com/arduino-libraries/NTPClient)
- [Timezone](https://github.com/JChristensen/Timezone)
- (ESP8266WiFi (part of ESP8266 core)) now using ESP8266WiFiMulti
- WiFiUdp (part of ESP8266 core)
