void setupNTPClient() {
  timeClient.begin();
  timeClient.update();
}

void updateClock() {
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime(); //comment out for testing
  char buf[10];
  getTimeString(epochTime, buf);
  markHours(epochTime);
  ledDisplay.setString(buf);
  ledDisplay.show();
  delay(1);
  FastLED.show();
  
  //Serial.print(buf);
  //Serial.println("");
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
