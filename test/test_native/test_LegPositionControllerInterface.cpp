#include "Leg.hpp"
#include "LegPositionController.hpp"
#include <gtest/gtest.h>

namespace logic::leg {
    TEST(LegPositionController, test_initialise_controller) {
        LegPositionController controller = LegPositionController();
        FootCoordinates coordinates;
        coordinates.x.SetCoordinate_mm(0);
        coordinates.y.SetCoordinate(2.0);
        ASSERT_EQ(coordinates.x, controller.GetX());
        ASSERT_EQ(coordinates.y, controller.GetY()); //(sin(60.0*Constants::PI/180.0) * 2.0) 
        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[0], controller.GetLegRange().x[0].GetCoordinate());
        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[1], controller.GetLegRange().x[1].GetCoordinate());
        ASSERT_EQ(Constants::Y_ABSOLUTE_RANGE[0], controller.GetLegRange().y[0].GetCoordinate());
        ASSERT_EQ(Constants::Y_ABSOLUTE_RANGE[1], controller.GetLegRange().y[1].GetCoordinate());
    }

    TEST(LegPositionController, test_CalculateYPosition) {
        LegPositionController controller = LegPositionController();

        ASSERT_EQ(RESULT_OK, controller.CalculateYPosition(controller.GetLegRange().x[0]));
        ASSERT_NEAR(controller.GetFootOnGroundY().GetCoordinate(), controller.GetY().GetCoordinate(), 0.001);

        controller.CalculateYPosition(controller.GetLegRange().x[1]);
        ASSERT_NEAR(controller.GetFootOnGroundY().GetCoordinate(), controller.GetY().GetCoordinate(), 0.001);

        controller.CalculateYPosition((controller.GetLegRange().x[0].GetCoordinate() + controller.GetLegRange().x[1].GetCoordinate()) / 2);
        ASSERT_NEAR(controller.GetFootUpY().GetCoordinate(), controller.GetY().GetCoordinate(), 0.001);
    }

    TEST(LegPositionController, test_Find_XY_Position) {
        LegPositionController controller = LegPositionController();

        ServosPositions positions;
        positions.upperServoAngle = 5.0 * Constants::PI / 6.0;
        positions.lowerServoAngle = -Constants::PI / 6.0;

        FootCoordinates coordinates = controller.FindXYPosition(positions);
        float expectedX = 0;
        float expectedY = 1.0000;
        ASSERT_NEAR(expectedX, coordinates.x.GetCoordinate(), 0.001);
        ASSERT_NEAR(expectedY, coordinates.y.GetCoordinate(), 0.001);
    }

    TEST(LegPositionController, test_CalculateNextCoordinates) {
        LegPositionController controller = LegPositionController();
        ASSERT_NEAR(0.0, controller.GetX().GetCoordinate_mm(), 0.001);
        FootTargetPosition target;
        target.footOnGround = false;
        target.x.SetCoordinate_mm(6.5);
        SingleCoordinate nextPosition;
        nextPosition.SetCoordinate_mm(Constants::DELTA_X_MM);
        FootCoordinates actual = controller.FindNextCoordinates(target);

        ASSERT_NEAR(nextPosition.GetCoordinate_mm(), actual.x.GetCoordinate_mm(), 0.001);
        ASSERT_EQ(RESULT_OK, controller.CalculateYPosition(nextPosition));
        ASSERT_EQ(controller.GetY().GetCoordinate_mm(), actual.y.GetCoordinate_mm());

        for (int i = 1; i < target.x.GetCoordinate_mm() / Constants::DELTA_X_MM - 1; i++) {
            actual = controller.FindNextCoordinates(target);
            nextPosition.SetCoordinate_mm(nextPosition.GetCoordinate_mm() + Constants::DELTA_X_MM);
            ASSERT_NEAR(nextPosition.GetCoordinate_mm(), actual.x.GetCoordinate_mm(), 0.001);
            ASSERT_EQ(RESULT_OK, controller.CalculateYPosition(nextPosition));
            ASSERT_EQ(controller.GetY().GetCoordinate_mm(), actual.y.GetCoordinate_mm());
        }

        actual = controller.FindNextCoordinates(target);
        nextPosition = target.x;
        ASSERT_NEAR(6.5, actual.x.GetCoordinate_mm(), 0.001);
        ASSERT_EQ(RESULT_OK, controller.CalculateYPosition(nextPosition));
        ASSERT_EQ(controller.GetY(), actual.y);

        target.x.SetCoordinate_mm(5.5);
        target.footOnGround = true;
        actual = controller.FindNextCoordinates(target);
        ASSERT_NEAR(5.5, actual.x.GetCoordinate_mm(), 0.001);
        ASSERT_NEAR(controller.GetFootOnGroundY().GetCoordinate(), actual.y.GetCoordinate(), 0.001);
    }

    TEST(LegPositionController, test_CalculateServoPositions_x0_KneeBack) {
        FootCoordinates coordinates;
        coordinates.x = 0;
        coordinates.y = 1.7320f;
        LegPositionController controller = LegPositionController(coordinates);
        ServosPositions expectedPositions;
        expectedPositions.lowerServoAngle = Constants::PI * 150.0f / 180.0f;
        expectedPositions.upperServoAngle = Constants::PI * 60.0f / 180.0f;
        ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
        ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
    }

    TEST(LegPositionController, test_CalculateServoPositions_x0_KneeFront) {
        LegPositionController controller = LegPositionController(0, 1.7320f, Side::KNEE_FRONT);
        ServosPositions expectedPositions;
        expectedPositions.upperServoAngle = Constants::PI * 120.0f / 180.0f;
        expectedPositions.lowerServoAngle = Constants::PI * 30.0f / 180.0f;
        ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
        ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
    }

    TEST(LegPositionController, test_CalculateServoPositions_x05_KneeBack) {
        float x = 0.5f, y = 1.7320f;
        LegPositionController controller = LegPositionController(x, y, Side::KNEE_BACK);
        ServosPositions expectedPositions;
        expectedPositions.upperServoAngle = 1.402044982f;
        expectedPositions.lowerServoAngle = 2.471000527f;
        ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
        ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
    }

    TEST(LegPositionController, test_CalculateServoPositions_x05_KneeFront) {
        float x = 0.5f, y = 1.7320f;
        LegPositionController controller = LegPositionController(x, y, Side::KNEE_FRONT);
        ServosPositions expectedPositions;
        expectedPositions.upperServoAngle = 2.302249182f;
        expectedPositions.lowerServoAngle = 0.670592127f;

        ASSERT_NEAR(expectedPositions.lowerServoAngle, controller.CalculateServoPositions().lowerServoAngle, 0.1);
        ASSERT_NEAR(expectedPositions.upperServoAngle, controller.CalculateServoPositions().upperServoAngle, 0.1);
    }
} // namespace logic::leg