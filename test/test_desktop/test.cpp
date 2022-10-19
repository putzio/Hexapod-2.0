#include <unity.h>
#include "pwm_driver.hpp"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_init() {
    Pwm_driver driver (2);
    TEST_ASSERT_EQUAL(2, driver.GetPin());
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_init);
    UNITY_END();
}