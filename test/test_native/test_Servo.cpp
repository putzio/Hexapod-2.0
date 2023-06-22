#include <gtest/gtest.h>

#include "Servo.hpp"

namespace logic::leg {
    TEST(Servo, test_servo_init) {
        Servo servo = Servo();

        ASSERT_NEAR(DEFAULT_SERVO_ANGLE, servo.GetCurrentAngle(), 0.001);
    }

    TEST(Servo, test_SetTargetAngle) {
        Servo servo = Servo();
        float expected = 0.2137f;

        ASSERT_EQ(RESULT_OK, servo.SetTargetAngle(expected));

        ASSERT_EQ(expected, servo.GetTargetAngle());
    }


    TEST(Servo, test_GoToTargetAngle) {
        Servo servo = Servo();

        float expectedAngle = Constants::PI / 3.0, expectedStep = Constants::PI / 60.0;
        float floatError = Constants::PI / 1800;//0.1 degree

        ASSERT_EQ(RESULT_OK, servo.SetTargetAngle(expectedAngle, expectedStep));

        ASSERT_NEAR(expectedAngle, servo.GetTargetAngle(), floatError);
        ASSERT_NEAR(expectedStep, servo.GetAngleChangingStep(), floatError);

        expectedAngle = Constants::PI / 2.0;
        ASSERT_NEAR(expectedAngle, servo.GetCurrentAngle(), floatError);
        for (int i = 0; i < 10; i++) {
            expectedAngle -= expectedStep;
            servo.GoToTargetAngle();
            ASSERT_NEAR(expectedAngle, servo.GetCurrentAngle(), floatError);
        }
        //Constants::PI / 2  - Constants::PI / 6 * 10 = Constants::PI / 3
        ASSERT_EQ(RESULT_SERVO_IN_TARGET_POSITION, servo.GoToTargetAngle());//this method call should not change anything
        expectedAngle = Constants::PI / 3;
        ASSERT_NEAR(expectedAngle, servo.GetCurrentAngle(), floatError);
    }

    TEST(Servo, test_GoToTargetAngle_Velocity_Eq_0) {
        Servo servo = Servo();

        float expectedAngle = Constants::PI / 3.0;
        float floatError = Constants::PI / 1800;//0.1 degree
        ASSERT_EQ(RESULT_OK, servo.SetTargetAngle(expectedAngle));
        Result expected = Result::RESULT_SERVO_VELOCITY_EQ_0;
        ASSERT_EQ(expected, servo.GoToTargetAngle());
    }
} // namespace logic::leg