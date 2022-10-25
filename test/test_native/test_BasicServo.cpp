#include "BasicServo.hpp"
#include <gtest/gtest.h>

TEST(BasicServo, test_initialises_BasicServo)
{
    BasicServo servo;
    servo.EnableServo();
    ASSERT_EQ(true, servo.enabled);
}