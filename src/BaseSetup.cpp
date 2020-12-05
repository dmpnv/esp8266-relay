/*
 Setup implementation
*/

#include "BaseSetup.h"
#include "Debug.h"

BaseSetup::BaseSetup(const char* configFile, const std::vector<AbstractService*>& vec) {
    this->fileName = configFile;
    this->init(vec);
}

void BaseSetup::init(const std::vector<AbstractService*>& vec) {
  if (!LittleFS.begin()) {
    LOGE("Failed to init LittleFS");
    return;
  }
  File configFile = LittleFS.open(fileName, "r");
  if (!configFile) {
    LOGE("Failed to open config file");
  }
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  configFile.close();
  StaticJsonDocument<200> doc;
  auto error = deserializeJson(doc, buf.get());
  if (error) {
    LOGE("Failed to parse config file");
    return;
  }

  LOG("--> parsed config file, reading properties ...");
  for (auto& it : vec) { 
    it->readProperties(doc);
  } 
}
