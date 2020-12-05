#ifndef WiFiClientService_h
#define WiFiClientService_h

#include "AbstractService.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#define CLIENT_CERTIFICATE_KEY "clientCertificate"
#define DEFAULT_CLIENT_CERTIFICATE "client.crt"
#define CLIENT_PRIVATEKEY_KEY "clientKey"
#define DEFAULT_CLIENT_PKEY "client.key"
#define CA_CERTIFICATE_KEY "caCertificate"
#define DEFAULT_CA_CERTIFICATE "ca.crt"
#define ALLOW_SELF_SIGNED_KEY "allowSelfSigned"


class WiFiClientService : public AbstractService {
private:
    String clientCertificate = DEFAULT_CLIENT_CERTIFICATE;
    String clientKey = DEFAULT_CLIENT_PKEY;
    String caCertificate = DEFAULT_CA_CERTIFICATE;
    bool allowSelfSigned = true;
    WiFiClientSecure wifiClient;
public:
    void readProperties(JsonDocument& doc);
    bool loadCertificates();
    bool verifyTLSConnection(String host, uint port);
    Client& getWiFiClient() { return wifiClient;}
};

#endif