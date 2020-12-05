#ifndef TimeService_h
#define TimeService_h

#include "AbstractService.h"

#define TZ_KEY "tz"
#define DEFAULT_TZ ""
#define NTP_SERVER1_KEY "ntpServer1"
#define DEFAULT_NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2_KEY "ntpServer2"
#define DEFAULT_NTP_SERVER2 "0.pool.ntp.org"
#define NTP_SERVER3_KEY "ntpServer3"
#define DEFAULT_NTP_SERVER3 "1.pool.ntp.org"

class TimeService : public AbstractService {
private:
    String tz = DEFAULT_TZ;
    String ntpServer1 = DEFAULT_NTP_SERVER1;
    String ntpServer2 = DEFAULT_NTP_SERVER2;
    String ntpServer3 = DEFAULT_NTP_SERVER3;
public:
    void readProperties(JsonDocument& doc);
    void syncTime();
};

#endif