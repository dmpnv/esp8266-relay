#include <ESP8266WiFi.h>
#include <time.h>
#include <FS.h>
#include <LittleFS.h>
#include "WiFiClientService.h"
#include "Debug.h"

void WiFiClientService::readProperties(JsonDocument& doc) {
    LOG("--> WiFiClientService::readProperties() ...");
    if (doc.containsKey(CLIENT_CERTIFICATE_KEY)) {
        this->clientCertificate = (const char *)doc[CLIENT_CERTIFICATE_KEY];
    }
    if (doc.containsKey(CLIENT_PRIVATEKEY_KEY)) {
        this->clientKey = (const char *)doc[CLIENT_PRIVATEKEY_KEY];
    }
    if (doc.containsKey(CA_CERTIFICATE_KEY)) {
        this->caCertificate = (const char *)doc[CA_CERTIFICATE_KEY];
    }
    if (doc.containsKey(ALLOW_SELF_SIGNED_KEY)) {
        this->allowSelfSigned = doc[ALLOW_SELF_SIGNED_KEY];
    }
}

bool WiFiClientService::loadCertificates() {
    LOG("--> Loading certificates ...");
    File clientCertificateFile = LittleFS.open(this->clientCertificate, "r");
    if (!clientCertificateFile) {
        LOGE("==> Failed to open client certificate file");
        return false;
    }
    if (wifiClient.loadCertificate(clientCertificateFile)) {
        LOG("--> Loaded client certificate");
    }else {
        LOGE("==> Failed load client certificate");
    }
    clientCertificateFile.close();

    File privateKey = LittleFS.open(this->clientKey, "r");
    if (!privateKey) {
        LOGE("==> Failed to open private key file");
        return false;
    }
    if (wifiClient.loadPrivateKey(privateKey)) {
        LOG("--> Loaded private key");
    }else {
        LOGE("==> Failed load private key");
    }
    privateKey.close();

    File caCertificateFile = LittleFS.open(this->caCertificate, "r");
    if (!caCertificateFile) {
        LOGE("==> Failed to open CA certificate");
        return false;
    }
    if (wifiClient.loadCACert(caCertificateFile)) {
        LOG("--> Loaded CA certificate");
    }else {
        LOGE("==> Failed load CA certificate");
    }
    caCertificateFile.close();
    if (this->allowSelfSigned) {
        wifiClient.allowSelfSignedCerts();
        LOG("--> Allowed self signed certificates");
    }
    LOG("--> Loaded all Certificates");
    return true;
}

bool WiFiClientService::verifyTLSConnection(String host, uint port) {
    if (!wifiClient.connect(host.c_str(), port)) {
        LOGT("--> Connected to %s:%d\n", host.c_str(), port);
    }else {
        LOGT("==> Failed to connect to %s:%d\n", host.c_str(), port);
        return false;
    }
    if (wifiClient.verifyCertChain(host.c_str())) {
        LOGT("--> Verified certificate chain, host: %s\n", host.c_str());
    }else {
        LOGT("==> Certificate Chain verification failed, host: %s\n", host.c_str());
        return false;
    }
    return true;
}

