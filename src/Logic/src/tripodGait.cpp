#include "tripodGait.hpp"

namespace logic::gait {
    Result TripodGait::GoToTheDefaultPosition() {
        typedef enum {
            MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION,
            LIFT_LEGS_IN_INCORRECT_POSITION,
            MOVE_LEGS_DOWN,
            LEGS_IN_DEFAULT_POSITION
        }DefaultPositionSteps;
        switch (step) {
        case MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION:
            for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
                if (!leg.footOnGround) {
                    leg.x = 0;
                }
            }
            step = MOVE_LEGS_DOWN;
            break;
        case LIFT_LEGS_IN_INCORRECT_POSITION:
            for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
                if (leg.x != 0) {
                    leg.footOnGround = false;
                }
            }
            step = MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION;
            break;
        case MOVE_LEGS_DOWN:
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
        case LEGS_IN_DEFAULT_POSITION:
            return RESULT_LEG_IN_TARGET_POSITION;
        default:
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }
} // namespace logic::gait