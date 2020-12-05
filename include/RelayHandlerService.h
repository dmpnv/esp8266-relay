#ifndef RelayHandlerService_h
#define RelayHandlerService_h

#include "AbstractService.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define MQTT_SERVER_HOST_KEY "mqttHost"
#define MQTT_SERVER_PORT_KEY "mqttPort"
#define DEFAULT_MQTT_SERVER_PORT 8883
#define RELAY_PIN_KEY "relayPin"
#define MQTT_NAME_KEY "mqttName"
#define DEFAULT_MQTT_NAME "Relay"
#define MQTT_QUEUE_KEY "mqttQueue"
#define DEFAULT_MQTT_QUEUE "inRelay"

class RelayHandlerService : public AbstractService {
private:
    PubSubClient client;
    String mqttServerHost = "";
    uint16_t mqttServerPort = DEFAULT_MQTT_SERVER_PORT;
    String mqttName = DEFAULT_MQTT_NAME;
    String mqttQueue = DEFAULT_MQTT_QUEUE;
public:
    void readProperties(JsonDocument& doc);
    bool connect(Client& wifiClient);
    bool connected();
    static void callback(char* topic, byte* payload, unsigned int length);
    void loop();
    String getMQTTServerHost() {return mqttServerHost;}
    uint16_t getMQTTServerPort(){ return mqttServerPort;}
};

#endif