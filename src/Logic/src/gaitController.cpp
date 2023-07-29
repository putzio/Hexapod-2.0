#include "gaitController.hpp"

namespace logic {

    GaitController::GaitController() {
        for (int i = 0; i < (int)legs.size(); i++) {
            legs[i] = leg::Leg(Constants::PI / 2, Constants::PI / 2, leg::Side::KNEE_BACK);
        }
    }


    Result GaitController::PeriodicProcess() {
        if (p_ptr_gaitInterface == nullptr) {
            return RESULT_WRONG_GAIT;
        }
        Result result = GoToPosition();
        if (result == RESULT_LEG_IN_TARGET_POSITION) {
            ReturnOnError(SetNewTarget());
        }

        for (int i = 0; i < (int)legs.size(); i++) {
            ReturnUnexpected(legs[i].LegPeriodicProcess(), RESULT_UNDEFINED_ERROR);
        }
        return RESULT_OK;
    }

    Result GaitController::ResetLegTargetPositions() {
        uint8_t legsSetCorrectly = UINT8_MAX;//UINT8_MAX means that all legs are set correctly
        for (int i = 0; i < (int)legs.size(); i++) {
            if (legs[i].SetNewTargetPosition(targetLegsPositions->legs[i]) != RESULT_OK) {
                legsSetCorrectly = i;
            }
        }
        if (legsSetCorrectly == UINT8_MAX) {
            return RESULT_OK;
        }
        else {
            return legs[legsSetCorrectly].SetNewTargetPosition(targetLegsPositions->legs[legsSetCorrectly]);
        }
    }

    Result GaitController::GoToPosition() {
        bool allLegsInPosition = true;
        for (int i = 0; i < (int)legs.size(); i++) {
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
        case FORWARD:
            ReturnOnError(p_ptr_gaitInterface->GoForeward());
            break;
        case BACKWARD:
            ReturnOnError(p_ptr_gaitInterface->GoBackward());
            break;
        case TURN_RIGHT:
            ReturnOnError(p_ptr_gaitInterface->TurnRight());
            break;
        case TURN_LEFT:
            ReturnOnError(p_ptr_gaitInterface->TurnLeft());
            break;
        case DEFAULT_POSITION: {
            leg::LegRange legRange = legs[0].GetRange();
            legRange.y[1] = 2.0;
            for (leg::Leg& leg : legs) {
                leg.SetLegRange(legRange);
            }
            ReturnOnError(p_ptr_gaitInterface->GoToTheDefaultPosition());
            break;
        }
        default:
            return RESULT_UNDEFINED_ERROR;
        }

        for (int i = 0; i < (int)legs.size(); i++) {
            ReturnOnError(legs[i].SetChangingStep(p_ptr_gaitInterface->GetChangingStepValues(), speed));
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
    Result GaitController::ChangeGait(gait::GaitType newGait) {
        if (p_ptr_gaitInterface != nullptr && newGait == p_ptr_gaitInterface->GetCurrentGait()) {
            return RESULT_CHOSEN_GAIT_IS_CURRENT_GAIT;
        }
        //stop the current gait?
        // p_ptr_gaitInterface = std::make_unique<gait::GaitInterface>(newGait);

        switch (newGait) {
        case gait::GaitType::TRIPOD: {
            p_ptr_gaitInterface = std::make_unique<gait::TripodGait>();
            break;
        }
        case gait::GaitType::CATERPILLAR: {
            p_ptr_gaitInterface = std::make_unique<gait::CaterpillarGait>();
            break;
        }
        default:
            return RESULT_UNDEFINED_ERROR;
        }

        targetLegsPositions = p_ptr_gaitInterface->GetTargetLegsPositionsPtr();
        // for (leg::Leg& leg : legs) {

        for (int i = 0; i < (int)legs.size(); i++) {
            ReturnOnError(legs[i].SetChangingStep(p_ptr_gaitInterface->GetChangingStepValues(), speed));
        }

        return SetNewTarget();
    }
    Result GaitController::ChangeSpeed(uint8_t newSpeed) {
        if (newSpeed > 10) {
            return RESULT_WRONG_SPEED;
        }
        speed = newSpeed;
        for (int i = 0; i < (int)legs.size(); i++) {
            ReturnOnError(legs[i].SetChangingStep(p_ptr_gaitInterface->GetChangingStepValues(), speed));
        }
        return RESULT_OK;
    }
    std::array<leg::ServosPositions, 6> GaitController::GetSerovAngles() {
        std::array<leg::ServosPositions, 6> result;
        for (int i = 0; i < (int)legs.size(); i++) {
            result[i] = legs[i].p_servos.GetCurrentServoPositions();
        }
        return result;
    }
}