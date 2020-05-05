#define FASTLED_ALLOW_INTERRUPTS 0 //Needed or else WS2812 will flicker

#include <FastLED.h>
#include <WS2812DisplayDriver.h>
#include <secrets.h>
#include <NTPClient.h>
#include <Timezone.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// ------------- Display -------------
#define NUM_ROWS 19
#define NUM_LINES 5
#define NUM_LEDS NUM_ROWS*NUM_LINES
#define DATA_PIN 2
#define MAX_DISPLAY_BRIGHTNESS 80
#define MIMIMUM_LIGHT_THRESHOLD 0
#define AMBIENT_STANDBY_THRESHOLD 10
#define MILLIS_SHOW_DATE 5000


CRGB leds[NUM_LEDS];
CRGB frameBuffer[NUM_ROWS][NUM_LINES];
Display ledDisplay(frameBuffer, leds, true);


// ------------- Ambient Light -------------
#define ANALOG_PIN A0

int outsideBrightness = 0;
int displayBrightness = 0;
const float alpha = 0.01;
double dataFiltered[] = {0, 0};
boolean standby = false;

// ------------- Network -------------
WiFiUDP ntpUDP;


// ------------- NTP Time -------------
NTPClient timeClient(ntpUDP);
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       // Central European Standard Time
Timezone CE(CEST, CET);

// ------------- Timing -------------
uint32_t displayUpdateMillis = 0;
uint32_t displayUpdateInterval = 1000;

uint32_t brightnessUpdateMillis = 0;
uint32_t brightnessUpdateInterval = 20;

// ------------- Marking -------------
#define DEFAULT_COLOR CRGB(255, 255, 255)
#define QUARTERHOUR_COLOR CRGB(255, 255, 0)
#define LEED_COLOR CRGB(255, 127, 0)
#define DATE_COLOR CRGB(0, 255, 127)

#define MARKTIME 3


void setup() {
  Serial.begin(115200);
  setupWifi();
  setupNTPClient();
  setupDisplay();
  setupAmbientSensor();
  Serial.println("");
  Serial.println("Setup complete. Waiting 5 sec to avoid deadlock in case of high power draw from leds");
  delay(5000); //Waiting 5 sec to avoid deadlock in case of high power draw from leds
  Serial.println("Finished");
}

//time_t epochTime = 1588505815; //for testing

void loop() {
  if (millis() - displayUpdateMillis > displayUpdateInterval) {
    //epochTime++; //For testing
    displayUpdateMillis = millis();
    updateDisplay();
  }

  if (millis() - brightnessUpdateMillis > brightnessUpdateInterval) {
    brightnessUpdateMillis = millis();
    updateBrightness();
  }
}
