#include <gtest/gtest.h>
#include "Logic/LegPositionController_KneeFront.hpp"


TEST(LegPositionController_KneeFront, test_calculateServoPositions) {
    LegPositionController_KneeFront controller = LegPositionController_KneeFront();
    float x = 0.5000;
    float y = 1.8660;//1+sin(60*)
    ServosPositions expected;
    expected.lowerServoAngle = Constants::PI / 3.0;
    expected.upperServoAngle = 2.0 * Constants::PI / 3.0;

    ServosPositions actual = controller.CalculateServoPositions(x, y);
    ASSERT_NEAR(expected.lowerServoAngle, actual.lowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.upperServoAngle, actual.upperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}

TEST(LegPositionController_KneeFront, test_calculateServoPositions_x_eq_zero) {
    LegPositionController_KneeFront controller = LegPositionController_KneeFront();
    float x = 0;
    float y = 1.0000;
    ServosPositions expected;
    expected.lowerServoAngle = -Constants::PI / 6.0;
    expected.upperServoAngle = 5.0 * Constants::PI / 6.0;

    ServosPositions actual = controller.CalculateServoPositions(x, y);
    ASSERT_NEAR(expected.lowerServoAngle, actual.lowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.upperServoAngle, actual.upperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}