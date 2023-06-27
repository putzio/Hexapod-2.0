#include <gtest/gtest.h>
#include "gaitController.hpp"
#include <memory>


namespace logic {
    TEST(GaitController, test_init) {
        GaitController gaitController = logic::GaitController();

        leg::ServosPositions expected = leg::ServosPositions();
        // expected.upperServoAngle = Constants::PI * 2.0f / 3.0f;
        expected.upperServoAngle = Constants::PI / 2;
        expected.lowerServoAngle = Constants::PI / 2;
        for (int i = 0; i < gaitController.GetSerovAngles().size(); i++) {
            ASSERT_EQ(expected, gaitController.GetSerovAngles()[i]);
        }
    }

    TEST(GaitController, test_Default_Tripod) {
        GaitController gaitController = logic::GaitController();
        ASSERT_EQ(RESULT_DIRECTION_NOT_CHOSEN, gaitController.ChangeGait(logic::gait::GaitInterface::TRIPOD));
        ASSERT_EQ(RESULT_OK, gaitController.ChangeDirection(logic::GaitController::DEFAULT_POSITION));

        ASSERT_EQ(RESULT_OK, gaitController.PeriodicProcess());
        while (gaitController.PeriodicProcess() != RESULT_LEG_IN_TARGET_POSITION) {
            //Do nothing
        }
        leg::ServosPositions expected = leg::ServosPositions();
        expected.upperServoAngle = Constants::PI / 3;
        expected.lowerServoAngle = Constants::PI / 1.2;//Check Calculations

        ASSERT_NEAR(expected.upperServoAngle, gaitController.GetSerovAngles()[0].upperServoAngle, 0.001);
        ASSERT_NEAR(expected.lowerServoAngle, gaitController.GetSerovAngles()[0].lowerServoAngle, 0.001);
    }

    TEST(GaitController, test_Foreward_Tripod_init) {
        GaitController gaitController = logic::GaitController();

        //Check if the leg position controller positions are correct
        ASSERT_NEAR(0.0, gaitController.legs[0].p_controller.GetCoordinates().x.GetCoordinate(), 0.001);

        ASSERT_EQ(RESULT_DIRECTION_NOT_CHOSEN, gaitController.ChangeGait(logic::gait::GaitInterface::TRIPOD));
        ASSERT_EQ(RESULT_OK, gaitController.ChangeDirection(logic::GaitController::FOREWARD));

        ASSERT_EQ(logic::gait::GaitInterface::TRIPOD, gaitController.p_ptr_gaitInterface->GetCurrentGait());
        ASSERT_EQ(logic::GaitController::FOREWARD, gaitController.direction);
    }

    TEST(GaitController, test_Foreward_Tripod_walk) {
        GaitController gaitController = logic::GaitController();

        ASSERT_EQ(RESULT_DIRECTION_NOT_CHOSEN, gaitController.ChangeGait(logic::gait::GaitInterface::TRIPOD));
        ASSERT_EQ(RESULT_OK, gaitController.ChangeDirection(logic::GaitController::FOREWARD));
        ASSERT_EQ(RESULT_OK, gaitController.ResetLegTargetPositions());
        ASSERT_EQ(RESULT_OK, gaitController.PeriodicProcess());

        //Check if the leg target positions in the gait interface are correct
        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[1], gaitController.p_ptr_gaitInterface->GetTargetLegsPositionsPtr()->legs[0].x.GetCoordinate());
        ASSERT_EQ(false, gaitController.p_ptr_gaitInterface->GetTargetLegsPositionsPtr()->legs[0].footOnGround);
        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[0], gaitController.p_ptr_gaitInterface->GetTargetLegsPositionsPtr()->legs[1].x.GetCoordinate());
        ASSERT_EQ(true, gaitController.p_ptr_gaitInterface->GetTargetLegsPositionsPtr()->legs[1].footOnGround);

        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[1], gaitController.targetLegsPositions->legs[0].x.GetCoordinate());
        ASSERT_EQ(false, gaitController.targetLegsPositions->legs[0].footOnGround);
        ASSERT_EQ(Constants::X_ABSOLUTE_RANGE[0], gaitController.targetLegsPositions->legs[1].x.GetCoordinate());
        ASSERT_EQ(true, gaitController.targetLegsPositions->legs[1].footOnGround);

        //Check if the leg position controller positions are correct
        ASSERT_NEAR(Constants::DELTA_X_MM, gaitController.legs[0].p_controller.GetCoordinates().x.GetCoordinate_mm(), 0.001);
        ASSERT_NEAR(Constants::DELTA_X_MM, gaitController.legs[1].p_controller.GetCoordinates().x.GetCoordinate_mm(), 0.001);

        // for (int i = 0; i < 100; i++)
        //     ASSERT_EQ(RESULT_OK, gaitController.PeriodicProcess());

        // logic::leg::FootCoordinates expectedCoordinates = logic::leg::FootCoordinates();
        // printf("Expected x: %f ", expectedCoordinates.x.GetCoordinate());

        // // leg::ServosPositions expected = leg::ServosPositions();
        // // expected.upperServoAngle = Constants::PI / 2;
        // // expected.lowerServoAngle = Constants::PI / 2;

        // // ASSERT_EQ(expected.upperServoAngle, gaitController.GetSerovAngles()[0].upperServoAngle);
        // // ASSERT_EQ(expected.lowerServoAngle, gaitController.GetSerovAngles()[0].lowerServoAngle);
        // // ASSERT_EQ(expected, gaitController.GetSerovAngles()[0]);
    }
}