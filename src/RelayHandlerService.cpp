#include <ESP8266WiFi.h>
#include <time.h>
#include <FS.h>
#include <LittleFS.h>
#include "RelayHandlerService.h"
#include "Debug.h"

int relayPin = 0;

#define MAX_TRIES 100

void RelayHandlerService::readProperties(JsonDocument& doc) {
    LOG("--> RelayHandlerService::readProperties() ...");
    if (doc.containsKey(MQTT_SERVER_HOST_KEY)) {
        this->mqttServerHost = (const char*)doc[MQTT_SERVER_HOST_KEY];
    }
    if (doc.containsKey(MQTT_SERVER_PORT_KEY)) {
        this->mqttServerPort = (uint16_t)doc[MQTT_SERVER_PORT_KEY];
    }
    if (doc.containsKey(RELAY_PIN_KEY)) {
        relayPin = (int)doc[RELAY_PIN_KEY];
    }
    if (doc.containsKey(MQTT_NAME_KEY)) {
        this->mqttName = (const char*)doc[MQTT_NAME_KEY];
    }
    if (doc.containsKey(MQTT_QUEUE_KEY)) {
        this->mqttQueue = (const char*)doc[MQTT_QUEUE_KEY];
    }
}

bool RelayHandlerService::connect(Client& wifiClient) {
    pinMode(relayPin, OUTPUT);
    LOGT("--> Connecting MQTTClient to %s:%d", this->mqttServerHost.c_str(), this->mqttServerPort);
    client.setServer(mqttServerHost.c_str(), mqttServerPort);
    client.setClient(wifiClient);
    client.setCallback(RelayHandlerService::callback);
    for( int n = 0; n < MAX_TRIES; n++ ) {
        if (client.connect(mqttName.c_str())) {
            LOGT("\n--> MQTTClient connected to %s:%d\n", mqttServerHost.c_str(), mqttServerPort);
            client.subscribe(mqttQueue.c_str());
            LOGT("--> MQTTClient subscribed to %s\n", mqttQueue.c_str());
            return true;
        }
        LOGS(".");
        delay(200);
    }

    LOGT("\n==> Error: MQTTClient failed to connect to %s:%d\n", mqttServerHost.c_str(), mqttServerPort);
    return false;
}

bool RelayHandlerService::connected() {
    return this->client.connected();
}

void RelayHandlerService::callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message = message + (char)payload[i];
    }
    LOGT("--> Message arrived in topic: %s, message: %s\n", topic, message.c_str());
    if (message == "1") {
        digitalWrite(relayPin, LOW);
    }
    if (message == "0") {
        digitalWrite(relayPin, HIGH);
    }
}

void RelayHandlerService::loop() {
    this->client.loop();
}
