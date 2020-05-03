enum {defaultState, markQuarterState, resetQuarterState, leedState};

void setupDisplay() {
  LEDS.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();

  LEDS.setBrightness(30);
  ledDisplay.setStringColor(CRGB(255, 255, 255));
}

void markHours(time_t utc) {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(utc, &tcr);

  static int markCase = defaultState;

  // ----- Mark quarter Hours -----
  static time_t startOfQuarterHour;
  if ((markCase == defaultState) && (minute(t) % 15 == 0)) {
    markCase = markQuarterState;
    startOfQuarterHour = utc;
    Serial.println("New Quarter Hour");
  }

  if ((markCase == markQuarterState) && (utc - startOfQuarterHour >= MARKTIME)) {
    markCase = resetQuarterState;
    Serial.println("Marktime elapsed");
  }

  if ((markCase == resetQuarterState) && (minute(t) % 15 != 0)) {
    markCase = defaultState;
    Serial.println("End of Quarter hour");
  }

  // ----- Mark 13:37 -----
  if ((hour(t) == 13) && (minute(t) == 37)) {
    markCase = leedState;
  }
  if ((markCase == leedState) && !((hour(t) == 13) && (minute(t) == 37)) ) {
    markCase = defaultState;
  }

  switch (markCase) {
    case defaultState:
      ledDisplay.setStringColor(DEFAULT_COLOR);
      break;
    case markQuarterState:
      ledDisplay.setStringColor(QUARTERHOUR_COLOR);
      break;
    case resetQuarterState:
      ledDisplay.setStringColor(DEFAULT_COLOR);
      break;
    case leedState:
      ledDisplay.setStringColor(LEED_COLOR);
  }
}
