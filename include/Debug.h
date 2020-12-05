#ifndef Debug_h
#define Debug_h

#ifndef LOG_DEBUG
#define LOG_DEBUG
#endif

#if defined(UNIT_TEST)
#   include <unity.h>
#   define LOG(msg)                TEST_MESSAGE(msg)
#   define LOGT(format,...)        TEST_MESSAGE(format); TEST_MESSAGE(##__VA_ARGS__)
#   define LOGE(msg)               TEST_MESSAGE(msg)
#   define LOGS(msg)               TEST_MESSAGE(msg)
#elif defined(LOG_DEBUG)
#   define LOG(msg)                Serial.println(msg)
#   define LOGT(format,...)        Serial.printf(format, ##__VA_ARGS__)
#   define LOGE(msg)               Serial.printf("%s:%d, error: %s\n", __FILE__, __LINE__, msg)
#   define LOGS(msg)               Serial.print(msg)
#else
#   define LOG(msg)
#   define LOGT(format,...)
#   define LOGE(msg)
#   define LOGS(msg)
#endif

#endif
