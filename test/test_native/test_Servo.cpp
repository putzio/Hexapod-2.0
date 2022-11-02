#include <gtest/gtest.h>

#include "Logic/ServoL.hpp"

TEST(Servo, test_servo_init)
{
    ServoL servo;

    ASSERT_EQ((uint16_t)(SERVO_MIN_MS + SERVO_MAX_MS) / 2, servo.currentPosition);
    // ASSERT_EQ(servo.msPosition, servo.position);
}

TEST(Servo, test_servo_position_90)
{
    ServoL servo;
    uint16_t pos = servo.currentPosition;
    servo.ChangePosition(90);
    ASSERT_EQ(90, servo.position);
    ASSERT_EQ(map(90, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS), servo.GetMsPosition());
}

TEST(Servo, test_servo_position_0)
{
    ServoL servo;
    uint16_t pos = servo.currentPosition;

    servo.ChangePosition(0);
    ASSERT_EQ(0, servo.position);

    servo.GoToPosition();
    ASSERT_EQ(map(0, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS), servo.GetMsPosition());
}
