enum {standbyState, showDateState, onState};
int displayState = standbyState;
uint32_t wakeupMillis = 0;

void updateDisplay() {
  boolean oldStandby = standby;
  standby = (displayBrightness > AMBIENT_STANDBY_THRESHOLD) ? false : true;

  if ((displayState == onState) && oldStandby && standby) {
    displayState = standbyState;
  }

  if (oldStandby && !standby) { //wakeup
    displayState = showDateState;
    wakeupMillis = millis();
  }

  if ((displayState = showDateState) && (millis() - wakeupMillis > MILLIS_SHOW_DATE)) {
    displayState = onState;
  }

  if ((displayState == showDateState) && !(((millis() - wakeupMillis) / 1000) % 2)) {
    updateDisplayedDate();
  }
  else {
    updateDisplayedTime();
  }
}

void setupDisplay() {
  strip.Begin();
  strip.Show();
  ledDisplay.setBrightness(30);
}

/*
  void setupDisplay() {
  LEDS.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();

  LEDS.setBrightness(30);
  ledDisplay.setStringColor(DEFAULT_COLOR);
  }
*/
