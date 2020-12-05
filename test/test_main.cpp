#include <Arduino.h>
#include <unity.h>
// #include <FS.h>
// #include <LittleFS.h>
#include "BaseSetup.h"

// void setUp(void) {
// }

// void tearDown(void) {
// }

void test_read_config_file(void) {
    TEST_MESSAGE("test message1");
    BaseSetup* setupInst = new BaseSetup();
    // bool res = LittleFS.begin();
    // TEST_ASSERT_TRUE(res);
    // File configFile = LittleFS.open("config.json", "r");
    // //TEST_ASSERT_NOT_EQUAL_MESSAGE(0, configFile, "");
    // TEST_MESSAGE("test message2");
    // if (!configFile) {
    //     //throw an exception "Failed to open config file"
    // }
    //     //TEST_ASSERT_EQUAL(13, LED_BUILTIN);
}

void test_led_state_high(void) {
    //digitalWrite(LED_BUILTIN, HIGH);
    //TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

void test_led_state_low(void) {
    //digitalWrite(LED_BUILTIN, LOW);
    //TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

void setup() {
    // waiting device to start
    delay(5000);
    UNITY_BEGIN();
    RUN_TEST(test_read_config_file);
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop() {
    delay(500);
    /*if (i < max_blinks)
    {
        RUN_TEST(test_led_state_high);
        delay(500);
        RUN_TEST(test_led_state_low);
        delay(500);
        i++;
    }
    else if (i == max_blinks) {
      UNITY_END(); // stop unit testing
    }*/
    UNITY_END();
}
