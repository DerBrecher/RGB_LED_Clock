enum {defaultState, markQuarterState, resetQuarterState, leedState};

void setupNTPClient() {
  timeClient.begin();
  timeClient.update();
}

void updateDisplayedDate() {
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime(); //comment out for testing
  char buf[10];
  getDateString(epochTime, buf);
  ledDisplay.setStringColor(DATE_COLOR);
  ledDisplay.setString(buf);
  ledDisplay.show();
  delay(1);
}

void updateDisplayedTime() {
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime(); //comment out for testing
  char buf[10];
  getTimeString(epochTime, buf);
  markHours(epochTime);
  ledDisplay.setString(buf);
  ledDisplay.show();
  delay(1);

  //Serial.print(buf);
  //Serial.println("");
}

void getDateString(time_t utc, char* buf) {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(utc, &tcr);
  sprintf(buf, "%.2d.%.2d", day(t), month(t));
}

void getTimeString(time_t utc, char* buf) {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(utc, &tcr);
  if (t % 2) {
    sprintf(buf, "%.2d:%.2d", hour(t), minute(t));
  }
  else {
    sprintf(buf, "%.2d %.2d", hour(t), minute(t));
  }
}

void markHours(time_t utc) {
  TimeChangeRule *tcr;
  time_t t = CE.toLocal(utc, &tcr);

  static int markState = defaultState;

  // ----- Mark quarter Hours -----
  static time_t startOfQuarterHour;
  if ((markState == defaultState) && (minute(t) % 15 == 0)) {
    markState = markQuarterState;
    startOfQuarterHour = utc;
    Serial.println("New Quarter Hour");
  }

  if ((markState == markQuarterState) && (utc - startOfQuarterHour >= MARKTIME)) {
    markState = resetQuarterState;
    Serial.println("Marktime elapsed");
  }

  if ((markState == resetQuarterState) && (minute(t) % 15 != 0)) {
    markState = defaultState;
    Serial.println("End of Quarter hour");
  }

  // ----- Mark 13:37 -----
  if ((hour(t) == 13) && (minute(t) == 37)) {
    markState = leedState;
  }
  if ((markState == leedState) && !((hour(t) == 13) && (minute(t) == 37)) ) {
    markState = defaultState;
  }

  switch (markState) {
    case defaultState:
      if (displayBrightness <= NIGHTTHRESHOLD) {
        ledDisplay.setStringColor(NIGHT_COLOR);
      }
      else {
        ledDisplay.setStringColor(DEFAULT_COLOR);
      }
      break;
    case markQuarterState:
      ledDisplay.setStringColor(QUARTERHOUR_COLOR);
      break;
    case resetQuarterState:
      if (displayBrightness <= NIGHTTHRESHOLD) {
        ledDisplay.setStringColor(NIGHT_COLOR);
      }
      else {
        ledDisplay.setStringColor(DEFAULT_COLOR);
      }
      break;
    case leedState:
      ledDisplay.setStringColor(LEED_COLOR);
  }
}
