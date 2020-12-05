#include "WiFiService.h"
#include "Debug.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define MAX_TRIES 100

void WiFiService::readProperties(JsonDocument& doc) {
    LOG("--> WiFiService::readProperties() ...");
    if (doc.containsKey(SSID_KEY)) {
        this->ssid = (const char *)doc[SSID_KEY];
    }
    if (doc.containsKey(WPA_KEY)) {
        this->wpaKey = (const char *)doc[WPA_KEY];
    }
}

void WiFiService::startWiFi() {
  LOGT("--> Connecting to %s ", this->ssid.c_str());
  WiFi.begin(this->ssid, this->wpaKey);
  delay(200);
  for( int n = 0; n < MAX_TRIES; n++ ) {
    if (WiFi.status() == WL_CONNECTED) {
      LOGT("\n--> Connected to %s, local IP: %s\n", this->ssid.c_str(), WiFi.localIP().toString().c_str());
      break;
    }
    LOGS(".");
    delay(200);
  }
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    LOGE("==> Unable to connect, restarting ...");
    ESP.restart();
  }
}

bool WiFiService::connected() {
    return WiFi.status() == WL_CONNECTED;
}
