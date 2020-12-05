#include <ArduinoJson.h>

#ifndef AbstractService_h
#define AbstractService_h

class AbstractService {
public:
    virtual void readProperties(JsonDocument& doc);
};

#endif