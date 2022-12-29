#include <gtest/gtest.h>

#include "Logic/ServoL.hpp"

TEST(Servo, test_servo_init)
{
    ServoL servo;

    ASSERT_EQ((uint16_t)(SERVO_MIN_MS + SERVO_MAX_MS) / 2, servo.currentPosition);
    // ASSERT_EQ(servo.msPosition, servo.position);
}

TEST(Servo, test_ChangePosition_to_90)
{
    ServoL servo;
    uint16_t pos = servo.currentPosition;

    servo.ChangePosition(90);

    ASSERT_EQ(90, servo.position);
    ASSERT_EQ(servo.MapPositionToMs(90), servo.GetMsPosition());
    ASSERT_EQ(false, servo.done);
}

TEST(Servo, test_ChangePosition_to_0)
{
    ServoL servo;
    uint16_t pos = servo.currentPosition;

    servo.ChangePosition(0);

    ASSERT_EQ(0, servo.position);
    ASSERT_EQ(servo.MapPositionToMs(0), servo.GetMsPosition());
    ASSERT_EQ(false, servo.done);
}

TEST(Servo, test_ChangePosition_to_0_and_GoToPosition)
{
    ServoL servo;
    uint16_t pos = servo.currentPosition;

    servo.ChangePosition(0);
    servo.GoToPosition();
    uint8_t v = 2;
    servo.ChangeVelocityLimits(v,v);
    const int16_t* limits = servo.GetVelocityLimits();

    //expected = current position
    uint16_t expected = (SERVO_MIN_MS + SERVO_MAX_MS) / 2;
    expected -= servo.GetVelocity();//v
    ASSERT_EQ(expected, servo.GetPwmValue());
    ASSERT_EQ(v, limits[1]);

    for(int i = 0; i < (expected - SERVO_MIN_MS)/v; i++)
    {
        servo.GoToPosition();
    }
    ASSERT_EQ(SERVO_MIN_MS, servo.GetPwmValue());
}

TEST(Servo, test_Write_45)
{
    ServoL servo;

    uint16_t expected = 45;
    servo.Write(expected);

    ASSERT_EQ(expected, servo.position);
    
    expected = servo.MapPositionToMs(expected);
    ASSERT_EQ(expected, servo.GetMsPosition());
    ASSERT_EQ(expected, servo.GetPwmValue());
}   