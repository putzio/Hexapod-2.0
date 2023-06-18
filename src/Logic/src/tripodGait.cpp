#include "tripodGait.hpp"

namespace logic::gait {
    Result TripodGait::GoForeward() {
        typedef enum {
            LIFT_LEGS_AND_MOVE_THEM_FORWARD,
            LOWER_LEGS_MOVE_THEM_BACKWARD
        } FirstGroupOfLegsSteps;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_THEM_FORWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LOWER_LEGS_MOVE_THEM_BACKWARD;
            break;
        }
        case LOWER_LEGS_MOVE_THEM_BACKWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            step = LIFT_LEGS_AND_MOVE_THEM_FORWARD;
            break;
        }
        }
        return RESULT_OK;
    }

    Result TripodGait::GoToTheDefaultPosition() {
        switch (step) {
        case MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION: {
            bool allLegsOnTheGround = true;
            for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
                if (!leg.footOnGround) {
                    leg.x = 0;
                    allLegsOnTheGround = false;
                }
            }
            if (allLegsOnTheGround) {
                for (int i : firstGroupOfLegs) {
                    targetLegsPositions.legs[i].x = 0;
                    targetLegsPositions.legs[i].footOnGround = false;
                }
            }
            step = MOVE_LEGS_DOWN;
            break;
        }
        case LIFT_LEGS_IN_INCORRECT_POSITION: {
            for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
                if (leg.x != 0) {
                    leg.footOnGround = false;
                }
            }
            step = MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION;
            break;
        }
        case MOVE_LEGS_DOWN: {
            bool allLegsAreInTheirDefaultPosition = true;
            for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
                leg.footOnGround = true;
                if (leg.x != 0) {
                    allLegsAreInTheirDefaultPosition = false;
                }
            }
            if (allLegsAreInTheirDefaultPosition) {
                step = LEGS_IN_DEFAULT_POSITION;
            }
            else {
                step = LIFT_LEGS_IN_INCORRECT_POSITION;
            }
            break;
        }
        case LEGS_IN_DEFAULT_POSITION:
            return RESULT_LEG_IN_TARGET_POSITION;
        default:
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

} // namespace logic::gait