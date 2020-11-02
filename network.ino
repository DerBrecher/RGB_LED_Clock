void maintainWifi(){
  wifiMulti.run(CONNECTTIMEOUTMS);
}

void setupWifi() {
  WiFi.mode(WIFI_STA);

  wifiMulti.addAP(SSIDHDS, WPA2HDS);
  wifiMulti.addAP(SSIDHDS2, WPA2HDS2);
  wifiMulti.addAP(SSIDSB, WPA2SB);
}
