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

        for (int i = 0; i < 1000; i++)
            ASSERT_EQ(RESULT_OK, gaitController.PeriodicProcess());

        leg::ServosPositions expected = leg::ServosPositions();
        expected.upperServoAngle = Constants::PI / 2;
        expected.lowerServoAngle = Constants::PI / 2;

        ASSERT_EQ(expected.upperServoAngle, gaitController.GetSerovAngles()[0].upperServoAngle);
        ASSERT_EQ(expected.lowerServoAngle, gaitController.GetSerovAngles()[0].lowerServoAngle);
        ASSERT_EQ(expected, gaitController.GetSerovAngles()[0]);
    }

    TEST(GaitController, test_Foreward_Tripod) {
        GaitController gaitController = logic::GaitController();
        ASSERT_EQ(RESULT_DIRECTION_NOT_CHOSEN, gaitController.ChangeGait(logic::gait::GaitInterface::TRIPOD));
        ASSERT_EQ(RESULT_OK, gaitController.ChangeDirection(logic::GaitController::FOREWARD));

        for (int i = 0; i < 100; i++)
            ASSERT_EQ(RESULT_OK, gaitController.PeriodicProcess());

        leg::ServosPositions expected = leg::ServosPositions();
        expected.upperServoAngle = Constants::PI / 2;
        expected.lowerServoAngle = Constants::PI / 2;

        ASSERT_EQ(expected.upperServoAngle, gaitController.GetSerovAngles()[0].upperServoAngle);
        ASSERT_EQ(expected.lowerServoAngle, gaitController.GetSerovAngles()[0].lowerServoAngle);
        ASSERT_EQ(expected, gaitController.GetSerovAngles()[0]);
    }
}