#include "gaitController.hpp"

namespace logic {
    GaitController::GaitController() {
        for (int i = 0; i < legs.size(); i++) {
            legs[i] = leg::Leg(Constants::PI / 2, Constants::PI / 2, leg::Side::KNEE_BACK);
        }
    }

    Result GaitController::PeriodicProcess() {
        if (p_ptr_gaitInterface == nullptr) {
            return RESULT_WRONG_GAIT;
        }

        if (GoToPosition() == RESULT_LEG_IN_TARGET_POSITION) {
            ReturnOnError(SetNewTarget());
        }

        for (int i = 0; i < legs.size(); i++) {
            ReturnUnexpected(legs[i].LegPeriodicProcess(), RESULT_UNDEFINED_ERROR);
        }
        return RESULT_OK;
    }
    Result GaitController::GoToPosition() {
        bool allLegsInPosition = true;
        for (int i = 0; i < legs.size(); i++) {
            if (legs[i].LegPeriodicProcess() != RESULT_LEG_IN_TARGET_POSITION) {
                allLegsInPosition = false;
            }
        }
        return allLegsInPosition ? RESULT_LEG_IN_TARGET_POSITION : RESULT_LEG_MOVING;
    }

    Result GaitController::SetNewTarget() {
        if (p_ptr_gaitInterface == nullptr) {
            return RESULT_WRONG_GAIT;
        }
        switch (direction) {
        case NONE:
            return RESULT_DIRECTION_NOT_CHOSEN;
        case FOREWARD:
            return p_ptr_gaitInterface->GoForeward();
        case BACKWARD:
            return p_ptr_gaitInterface->GoBackward();
        case TURN_RIGHT:
            return p_ptr_gaitInterface->TurnRight();
        case TURN_LEFT:
            return p_ptr_gaitInterface->TurnLeft();
        case DEFAULT_POSITION: {
            leg::LegRange legRange = legs[0].GetRange();
            legRange.y[1] = 2.0;
            for (leg::Leg& leg : legs) {
                leg.SetLegRange(legRange);
            }
            return p_ptr_gaitInterface->GoToTheDefaultPosition();
        }
        default:
            return RESULT_UNDEFINED_ERROR;
        }
        for (int i = 0; i < legs.size(); i++) {
            ReturnOnError(legs[i].SetNewTargetPosition(targetLegsPositions->legs[i]));
        }
        return RESULT_OK;
    }

    Result GaitController::ChangeDirection(Direction newDirection) {
        //stop the current direction at first?

        if (newDirection == direction) {
            return RESULT_OK;
        }
        direction = newDirection;
        return SetNewTarget();
    }
    Result GaitController::ChangeGait(gait::GaitInterface::Gait newGait) {
        if (p_ptr_gaitInterface != nullptr && newGait == p_ptr_gaitInterface->GetCurrentGait()) {
            return RESULT_OK;
        }
        //stop the current gait?
        // p_ptr_gaitInterface = std::make_unique<gait::GaitInterface>(newGait);

        switch (newGait) {
        case gait::GaitInterface::Gait::TRIPOD: {
            p_ptr_gaitInterface = std::make_unique<gait::TripodGait>();
            break;
        }
        }

        targetLegsPositions = p_ptr_gaitInterface->GetTargetLegsPositionsPtr();
        return SetNewTarget();
    }

    std::array<leg::ServosPositions, 6> GaitController::GetSerovAngles() {
        std::array<leg::ServosPositions, 6> result;
        for (int i = 0; i < legs.size(); i++) {
            result[i] = legs[i].p_servos.GetCurrentServoPositions();
        }
        return result;
    }
}