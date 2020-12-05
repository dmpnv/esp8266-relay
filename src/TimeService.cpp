#include <ESP8266WiFi.h>
#include <time.h>
#include "TimeService.h"
#include "Debug.h"

void TimeService::readProperties(JsonDocument& doc) {
    LOG("--> TimeService::readProperties() ...");
    if (doc.containsKey(TZ_KEY)) {
        this->tz = (const char*)doc[TZ_KEY];
    }
    if (doc.containsKey(NTP_SERVER1_KEY)) {
        this->ntpServer1 = (const char*)doc[NTP_SERVER1_KEY];
    }
    if (doc.containsKey(NTP_SERVER2_KEY)) {
        this->ntpServer2 = (const char*)doc[NTP_SERVER2_KEY];
    }
    if (doc.containsKey(NTP_SERVER3_KEY)) {
        this->ntpServer3 = (const char*)doc[NTP_SERVER3_KEY];
    }
}

void TimeService::syncTime() {
    LOGT("--> Synchronizing time: tz = %s, server1 = %s, server2 = %s, server3 = %s",
            this->tz.c_str(), this->ntpServer1.c_str(), this->ntpServer2.c_str(), this->ntpServer3.c_str());
    configTime(this->tz.c_str(), this->ntpServer1.c_str(), this->ntpServer2.c_str(), this->ntpServer3.c_str());
    time_t currentTime = time(0);
    while(currentTime <= 24*3600) {
        currentTime = time(0);
        LOGS(".");
        delay(200);
    }
        
    LOGT("\n--> Synchronized time, %s", ctime(&currentTime));
}