#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "Debug.h"
#include "BaseSetup.h"
#include "WiFiService.h"
#include "TimeService.h"
#include "WiFiClientService.h"
#include "RelayHandlerService.h"

#ifndef UNIT_TEST

#define DEFAULT_CONFIG_FILE "config.json"

WiFiService wifiService;
WiFiClientService wifiClientService;
RelayHandlerService relayHandlerService;

void setup() {
  // delay(5000);
  Serial.begin(115200);
  LOG("Setup ...");
  LOGT("--> create a Setup instance, fileName = %s\n", DEFAULT_CONFIG_FILE);
  TimeService timeService;
  BaseSetup baseSetup(DEFAULT_CONFIG_FILE, {&wifiService, &timeService, &wifiClientService, &relayHandlerService});
  wifiService.startWiFi();
  timeService.syncTime();
  wifiClientService.loadCertificates();
  // wifiClientService->verifyTLSConnection(relayHandlerService->getMQTTServerHost(), relayHandlerService->getMQTTServerPort());
}
#endif

#ifndef UNIT_TEST
void loop() {
  if (wifiService.connected()) {
    if (!relayHandlerService.connected()) {
      if (!relayHandlerService.connect(wifiClientService.getWiFiClient())) {
        LOGE("==> relayHandlerService failed to connect");
        delay(2000);
        ESP.reset();
      }
    } else {
      relayHandlerService.loop();
    }
  } else {
    LOGE("==> WiFi.status() != WL_CONNECTED ");
    delay(2000);
    ESP.reset();
  }
}
#endif
