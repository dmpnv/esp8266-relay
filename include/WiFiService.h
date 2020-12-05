#ifndef WiFiService_h
#define WiFiService_h

#include "AbstractService.h"

#define SSID_KEY "ssid"
#define DEFAULT_SSID "wifi"

#define WPA_KEY "wpaKey"

class WiFiService : public AbstractService {
private:
    String ssid = DEFAULT_SSID;
    String wpaKey = "";
public:
    void readProperties(JsonDocument& doc);
    void startWiFi();
    bool connected();
};

#endif
