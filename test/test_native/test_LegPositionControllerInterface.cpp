#include "../../src/Logic/inc/Leg.hpp"
#include "../../src/Logic/inc/LegPositionControllerInterface.hpp"
#include <gtest/gtest.h>

TEST(LegPositionControllerInterface, test_initialise_controller) {
    LegPositionControllerInterface controller = LegPositionControllerInterface();

    ASSERT_NEAR(0, controller.GetX(), 0.001);
    ASSERT_NEAR(1.7320f, controller.GetY(), 0.001); //(sin(60.0*Constants::PI/180.0) * 2.0)
}

TEST(LegPositionControllerInterface, test_CalculateYPosition) {
    LegPositionControllerInterface controller = LegPositionControllerInterface();

    controller.CalculateYPosition(controller.GetLegRange().x[0]);
    ASSERT_NEAR(controller.GetLegRange().y[1], controller.GetY(), 0.001);

    controller.CalculateYPosition(controller.GetLegRange().x[1]);
    ASSERT_NEAR(controller.GetLegRange().y[1], controller.GetY(), 0.001);

    controller.CalculateYPosition((controller.GetLegRange().x[0] + controller.GetLegRange().x[1]) / 2);
    ASSERT_NEAR(controller.GetLegRange().y[0], controller.GetY(), 0.001);
}

TEST(LegPositionControllerInterface, test_Find_XY_Position) {
    LegPositionControllerInterface controller = LegPositionControllerInterface();

    ServosPositions positions;
    positions.upperServoAngle = 5.0 * Constants::PI / 6.0;
    positions.lowerServoAngle = -Constants::PI / 6.0;

    controller.FindXYPosition(positions);
    float expectedX = 0;
    float expectedY = 1.0000;
    ASSERT_NEAR(expectedX, controller.GetX(), 0.001);
    ASSERT_NEAR(expectedY, controller.GetY(), 0.001);
}

TEST(LegPositionControllerInterface, test_CalculateNextCoordinates) {
    LegPositionControllerInterface controller = LegPositionControllerInterface();
    float targetX = 6.5;
    bool footOnGround = false;

    FootCoordinates actual = controller.FindNextCoordinates(targetX, footOnGround);
    ASSERT_NEAR(5.0, actual.x, 0.001);
    ASSERT_NEAR(controller.CalculateYPosition(5.0), actual.y, 0.001);

    actual = controller.FindNextCoordinates(targetX, footOnGround);
    ASSERT_NEAR(6.5, actual.x, 0.001);
    ASSERT_NEAR(controller.CalculateYPosition(6.5), actual.y, 0.001);

    targetX = 5.0;
    footOnGround = true;
    actual = controller.FindNextCoordinates(targetX, footOnGround);
    ASSERT_NEAR(5.0, actual.x, 0.001);
    ASSERT_NEAR(controller.GetLegRange().y[1], actual.y, 0.001);
}

TEST(LegPositionControllerInterface, test_CalculateServoPositions_x0_KneeBack) {
    LegPositionControllerInterface controller = LegPositionControllerInterface();
    ServosPositions expectedPositions;
    expectedPositions.lowerServoAngle = Constants::PI * 60.0f / 180.0f;
    expectedPositions.upperServoAngle = Constants::PI * 60.0f / 180.0f;
    ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
    ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
}

TEST(LegPositionControllerInterface, test_CalculateServoPositions_x0_KneeFront) {
    LegPositionControllerInterface controller = LegPositionControllerInterface(0, 1.7320f, Side::KNEE_FRONT);
    ServosPositions expectedPositions;
    expectedPositions.upperServoAngle = Constants::PI * 120.0f / 180.0f;
    expectedPositions.lowerServoAngle = Constants::PI * 30.0f / 180.0f;
    ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
    ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
}

TEST(LegPositionControllerInterface, test_CalculateServoPositions_x05_KneeBack) {
    float x = 0.5f, y = 1.7320f;
    LegPositionControllerInterface controller = LegPositionControllerInterface(x, y, Side::KNEE_BACK);
    ServosPositions expectedPositions;
    expectedPositions.upperServoAngle = 1.402044982f;
    expectedPositions.lowerServoAngle = 0.9002042f;
    ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
    ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
}

TEST(LegPositionControllerInterface, test_CalculateServoPositions_x05_KneeFront) {
    float x = 0.5f, y = 1.7320f;
    LegPositionControllerInterface controller = LegPositionControllerInterface(x, y, Side::KNEE_FRONT);
    ServosPositions expectedPositions;
    expectedPositions.upperServoAngle = 2.302249182f;
    expectedPositions.lowerServoAngle = 0.670592127f;

    ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
    ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
}