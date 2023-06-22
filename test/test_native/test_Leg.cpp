#include <gtest/gtest.h>
#include "Leg.hpp"
#include <memory>


namespace logic::leg {
    float CalculateNumberOfSteps(ServosPositions target, ServosPositions current, float changingStep);
    void CalculateServoPosition(ServosPositions& positions, ServosPositions& targetPositions, float changingStep);
    void PeriodicProcess(Leg& leg, ServosPositions target);
    void PeriodicProcess(Leg& leg);
    void FullPeriodicProcess(Leg& leg);
    FootTargetPosition GoForeward(uint8_t& step);

    TEST(Leg, test_init) {
        Leg leg = Leg(Side::KNEE_BACK);
        FootCoordinates coordinates;
        coordinates.x = 0;
        coordinates.y = 1.7320f;//sin(60.0 * Constants::PI / 180.0) * 20000.0;
        ASSERT_EQ(coordinates.x, leg.GetFootCoordinates().x);
        ASSERT_EQ(coordinates.y, leg.GetFootCoordinates().y);
        ASSERT_NEAR(Constants::PI / 180.0f, leg.GetChangingStep(), 0.0001);
        ASSERT_NEAR(Constants::PI / 3.0f, leg.p_servos.GetCurrentServoPositions().upperServoAngle, 0.001);
        ASSERT_NEAR(Constants::PI * 5.0f / 6.0f, leg.p_servos.GetCurrentServoPositions().lowerServoAngle, 0.001);
        // ASSERT_EQ(coordinates, leg.p_controller.GetCoordinates());
    }

    TEST(Leg, test_MoveJServos) {
        Leg leg = Leg(Side::KNEE_BACK);
        ServosPositions positions;
        positions.upperServoAngle = Constants::PI * 2.0f / 3.0f;
        positions.lowerServoAngle = Constants::PI * 1.0f / 6.0f;
        LegRange range = leg.GetRange();
        range.y[1] = 2;
        leg.SetLegRange(range);
        ServosPositions currentPositions = leg.p_servos.GetCurrentServoPositions();
        ASSERT_EQ(Result::RESULT_OK, leg.MoveJServos(positions));
        PeriodicProcess(leg, positions);
        ASSERT_EQ(Result::RESULT_LEG_IN_TARGET_POSITION, leg.LegPeriodicProcess());
    }

    TEST(Leg, test_SetNewTargetPosition_and_Periodic_Process) {
        Leg leg = Leg(Side::KNEE_BACK);
        FootTargetPosition coordinates;
        coordinates.x.SetCoordinate_mm(7);
        coordinates.footOnGround = true;
        ASSERT_EQ(RESULT_OK, leg.SetNewTargetPosition(coordinates));
        ServosPositions positions = leg.p_servos.GetCurrentServoPositions();
        ServosPositions targetPositions = leg.p_controller.CalculateServoPositions(leg.p_controller.GetCoordinates());
        FullPeriodicProcess(leg);
    }

    TEST(Leg, test_tripod_movements) {
        uint8_t step = 0;
        Leg leg = Leg(Constants::PI / 2, Constants::PI / 2, Side::KNEE_BACK);
        FootTargetPosition target = GoForeward(step);
        leg.SetChangingStep(Constants::PI * 2.0 / 180.0f);
        leg.SetNewTargetPosition(target);
        FullPeriodicProcess(leg);
        // ASSERT_EQ(Result::RESULT_LEG_IN_TARGET_POSITION, leg.LegPeriodicProcess());
    }

    float CalculateNumberOfSteps(ServosPositions target, ServosPositions current, float changingStep) {
        float steps = 0;
        if (std::abs(target.upperServoAngle - current.upperServoAngle) > std::abs(target.lowerServoAngle - current.lowerServoAngle)) {
            steps = std::abs(target.upperServoAngle - current.upperServoAngle) / changingStep;
        }
        else {
            steps = std::abs(target.lowerServoAngle - current.lowerServoAngle) / changingStep;
        }
        return steps;
    }

    void CalculateServoPosition(ServosPositions& positions, ServosPositions& targetPositions, float changingStep) {
        if (std::abs(positions.upperServoAngle - targetPositions.upperServoAngle) < changingStep) {
            positions.upperServoAngle = targetPositions.upperServoAngle;
        }
        else if (positions.upperServoAngle > targetPositions.upperServoAngle) {
            positions.upperServoAngle -= changingStep;
        }
        else {
            positions.upperServoAngle += changingStep;
        }

        if (std::abs(positions.lowerServoAngle - targetPositions.lowerServoAngle) < changingStep) {
            positions.lowerServoAngle = targetPositions.lowerServoAngle;
        }
        else if (positions.lowerServoAngle > targetPositions.lowerServoAngle) {
            positions.lowerServoAngle -= changingStep;
        }
        else {
            positions.lowerServoAngle += changingStep;
        }
    }
    void PeriodicProcess(Leg& leg, ServosPositions target) {
        ServosPositions currentPositions = leg.p_servos.GetCurrentServoPositions();
        float steps = CalculateNumberOfSteps(
            target,
            currentPositions,
            leg.GetChangingStep()
        ) - 1;
        for (int i = 0; i < steps; i++) {
            CalculateServoPosition(currentPositions, target, leg.GetChangingStep());
            Result r = leg.LegPeriodicProcess();
            ASSERT_EQ(Result::RESULT_LEG_MOVING, r);
            ASSERT_NEAR(currentPositions.upperServoAngle, leg.p_servos.GetCurrentServoPositions().upperServoAngle, 0.001);
            ASSERT_NEAR(currentPositions.lowerServoAngle, leg.p_servos.GetCurrentServoPositions().lowerServoAngle, 0.001);
        }
    }
    void PeriodicProcess(Leg& leg) {
        ServosPositions target = leg.p_controller.CalculateServoPositions(leg.p_controller.GetCoordinates());
        PeriodicProcess(leg, target);
    }

    void FullPeriodicProcess(Leg& leg) {
        float steps = leg.GetFinalTargetPosition().x.GetCoordinate() / Constants::DELTA_X;
        for (int i = 0; i < steps; i++) {
            PeriodicProcess(leg);
            if (i != (int)steps) {
                ASSERT_EQ(Result::RESULT_LEG_NEW_CONTROLLER_POSITION, leg.LegPeriodicProcess());
            }
            else {
                ASSERT_EQ(Result::RESULT_LEG_IN_TARGET_POSITION, leg.LegPeriodicProcess());
            }
        }
    }

    FootTargetPosition GoForeward(uint8_t& step) {
        typedef enum {
            LIFT_LEGS_AND_MOVE_THEM_FORWARD,
            LOWER_LEGS_MOVE_THEM_BACKWARD
        } FirstGroupOfLegsSteps;
        FootTargetPosition targetLegsPositions;
        float xForeward = 2;
        float xBackwards = -2;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_THEM_FORWARD: {
            targetLegsPositions.x = xForeward;
            targetLegsPositions.footOnGround = false;
            step = LOWER_LEGS_MOVE_THEM_BACKWARD;
            break;
        }
        case LOWER_LEGS_MOVE_THEM_BACKWARD: {
            targetLegsPositions.x = xBackwards;
            targetLegsPositions.footOnGround = true;
            step = LIFT_LEGS_AND_MOVE_THEM_FORWARD;
            break;
        }
        }
        return targetLegsPositions;
    }
} // namespace logic::leg