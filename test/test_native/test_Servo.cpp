#include <gtest/gtest.h>

#include "Logic/Servo.hpp"

TEST(Servo, test_servo_init){
    Servo servo = Servo();

    ASSERT_NEAR(DEFAULT_SERVO_ANGLE, servo.GetServoAngle(), 0.001);
}

TEST(Servo, test_GoToTargetAngle){
    Servo servo = Servo();
    
    float expectedAngle = PI / 3.0, expectedStep = PI / 60.0; 
    float floatError = PI / 1800;//0.1 degree
    
    servo.SetTargetAngle(expectedAngle, expectedStep);

    ASSERT_NEAR(expectedAngle, servo.GetTargetAngle(), floatError);
    ASSERT_NEAR(expectedStep, servo.GetAngleChangingStep(), floatError);
    
    expectedAngle = PI / 2.0;
    ASSERT_NEAR(expectedAngle, servo.GetServoAngle(), floatError);
    for(int i = 0; i < 10; i++)
    {
        expectedAngle -= expectedStep;
        servo.GoToTargetAngle();
        ASSERT_NEAR(expectedAngle, servo.GetServoAngle(), floatError);
    }
    //PI / 2  - PI / 6 * 10 = PI / 3
    servo.GoToTargetAngle();//this method call should not change anything
    expectedAngle = PI / 3;
    ASSERT_NEAR(expectedAngle, servo.GetServoAngle(), floatError);
}

TEST(Servo, test_GetAngleInMs){
    Servo servo = Servo();
    
    uint16_t expected = (servo.ANGLE_RANGE_MS[1] + servo.ANGLE_RANGE_MS[0]) / 2;//90 deg
    ASSERT_EQ(expected, servo.GetServoAngleInMs());

    servo.SetServoAngle(servo.ANGLE_RANGE[0]);
    expected = servo.ANGLE_RANGE_MS[0];
    ASSERT_EQ(expected, servo.GetServoAngleInMs());

    servo.SetServoAngle(servo.ANGLE_RANGE[1]);
    expected = servo.ANGLE_RANGE_MS[1];
    ASSERT_EQ(expected, servo.GetServoAngleInMs());
}