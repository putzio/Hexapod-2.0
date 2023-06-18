#include "../inc/gaitController.hpp"

namespace logic {
    GaitController::GaitController() {
        for (int i = 0; i < legs.size(); i++) {
            legs[i] = leg::Leg(leg::Side::KNEE_BACK);
        }
    }

    Result GaitController::PeriodicProcess() {
        if (p_ptr_gaitInterface == nullptr) {
            return RESULT_WRONG_GAIT;
        }

        if (GoToPosition() == RESULT_LEG_IN_TARGET_POSITION) {
            SetNewTarget();
        }
        return RESULT_OK;
    }
    Result GaitController::GoToPosition() {
        bool allLegsInPosition = true;
        for (leg::Leg& leg : legs) {
            if (leg.LegPeriodicProcess() != RESULT_LEG_IN_TARGET_POSITION) {
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
            return RESULT_OK;
        case FOREWARD:
            return p_ptr_gaitInterface->GoForeward();
        case BACKWARD:
            return p_ptr_gaitInterface->GoBackward();
        case TURN_RIGHT:
            return p_ptr_gaitInterface->TurnRight();
        case TURN_LEFT:
            return p_ptr_gaitInterface->TurnLeft();
        case DEFAULT_POSITION:
            return p_ptr_gaitInterface->GoToTheDefaultPosition();
        default:
            return RESULT_UNDEFINED_ERROR;
        }
        for (int i = 0; i < legs.size(); i++) {
            legs[i].SetNewTargetPosition(targetLegsPositions->legs[i]);
        }
    }

    Result GaitController::ChangeDirection(Direction newDirection) {
        //stop the current direction at first?

        if (newDirection == direction) {
            return RESULT_OK;
        }

        direction = newDirection;
        SetNewTarget();
    }
    Result GaitController::ChangeGait(gait::GaitInterface::Gait newGait) {
        if (p_ptr_gaitInterface != nullptr && newGait == p_ptr_gaitInterface->GetCurrentGait()) {
            return RESULT_OK;
        }
        //stop the current gait?
        // p_ptr_gaitInterface = std::make_unique<gait::GaitInterface>(newGait);
        typedef gait::GaitInterface::Gait Gait;
        switch (newGait) {
        case Gait::TRIPOD_WALK: {
            // p_ptr_gaitInterface = std::make_unique<gait::TripodWalk>();
            break;
        }
        }


        targetLegsPositions = p_ptr_gaitInterface->GetTargetLegsPositionsPtr();
        SetNewTarget();
    }
}