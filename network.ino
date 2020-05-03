void setupWifi() {
  WiFi.begin(SSIDHDS, WPA2HDS);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
}
