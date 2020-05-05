void setupAmbientSensor() {
  pinMode(ANALOG_PIN, INPUT);
}

void updateBrightness() {
  int newBrightness = analogRead(ANALOG_PIN);
  dataFiltered[1] = alpha * newBrightness + (1 - alpha) * dataFiltered[0];
  dataFiltered[0] = dataFiltered[1];
  outsideBrightness = dataFiltered[1];

  displayBrightness = map(outsideBrightness, MIMIMUM_LIGHT_THRESHOLD, 1023, 1, MAX_DISPLAY_BRIGHTNESS);
  displayBrightness = constrain(displayBrightness, 1, MAX_DISPLAY_BRIGHTNESS);
  LEDS.setBrightness(displayBrightness);
  FastLED.show();

  Serial.print("Outside ");
  Serial.print(outsideBrightness);
  Serial.print(" Display ");
  Serial.println(displayBrightness);
}
