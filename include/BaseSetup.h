/*
 This class is created to handle the setup phase
*/

#ifndef BaseSetup_h
#define BaseSetup_h

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <vector>
#include "AbstractService.h"
#include "Debug.h"

class BaseSetup {
private:
    const char* fileName;
    void init(const std::vector<AbstractService*>& vec);
public:
    BaseSetup(const char* configFile, const std::vector<AbstractService*>& vec);
    ~BaseSetup() {}
    const char* getFileName() { return fileName; }
};

#endif
