#include "BasicServo.hpp"
#include <gtest/gtest.h>

TEST(initialiseBasicServo, test_initialises_BasicServo)
{
    BasicServo servo;
    servo.EnableServo();
    ASSERT_EQ(true, servo.enabled);
}