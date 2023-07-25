#include "caterpillarGait.hpp"
#include <stdio.h>
namespace logic::gait {
    void CaterpillarGait::Error_Handler() {
        printf("In Error_Handler()\n");
        while (1) {
            // sleep_ms(1000);
        }
    }
    Result CaterpillarGait::GoForeward() {
        typedef enum {
            LIFT_FRONT_LEGS_AND_MOVE_THEM_FORWARD,
            LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY,
            LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY
        } FrontLegsSteps;
        switch (step) {
        case LIFT_FRONT_LEGS_AND_MOVE_THEM_FORWARD: {
            printf("LIFT_FRONT_LEGS_AND_MOVE_THEM_FORWARD\n");
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY: {
            printf("LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY\n");
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY: {
            printf("LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY\n");
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LIFT_FRONT_LEGS_AND_MOVE_THEM_FORWARD;
            break;
        }
        default:
            printf("ERROR: CaterpillarGait::GoForeward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

    Result CaterpillarGait::GoBackward() {
        typedef enum {
            LIFT_FRONT_LEGS_AND_MOVE_THEM_BACKWARD,
            LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_HALFWAY,
            LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_FULLY
        } FrontLegsSteps;
        switch (step) {
        case LIFT_FRONT_LEGS_AND_MOVE_THEM_BACKWARD: {
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_HALFWAY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_HALFWAY: {
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_FULLY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_FULLY: {
            for (int i : frontLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i].x = xHalfway;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LIFT_FRONT_LEGS_AND_MOVE_THEM_BACKWARD;
            break;
        }
        default:
            printf("ERROR: CaterpillarGait::GoBackward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

    Result CaterpillarGait::TurnRight() { printf("TurnRight\n"); return RESULT_OK; }
    Result CaterpillarGait::TurnLeft() { printf("TurnLeft\n"); return RESULT_OK; }


    Result CaterpillarGait::GoToTheDefaultPosition() { printf("GoToTheDefaultPosition\n"); return RESULT_OK; }
    //     typedef enum {
    //         MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION,
    //         LIFT_LEGS_IN_INCORRECT_POSITION,
    //         MOVE_LEGS_DOWN,
    //         LEGS_IN_DEFAULT_POSITION
    //     }DefaultPositionSteps;
    //     switch (step) {
    //     case MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION: {
    //         bool allLegsOnTheGround = true;
    //         for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
    //             if (!leg.footOnGround) {
    //                 leg.x = 0;
    //                 allLegsOnTheGround = false;
    //             }
    //         }
    //         if (allLegsOnTheGround) {
    //             for (int i : firstGroupOfLegs) {
    //                 targetLegsPositions.legs[i].x = 0;
    //                 targetLegsPositions.legs[i].footOnGround = false;
    //             }
    //         }
    //         step = MOVE_LEGS_DOWN;
    //         break;
    //     }
    //     case LIFT_LEGS_IN_INCORRECT_POSITION: {
    //         for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
    //             if (leg.x != 0) {
    //                 leg.footOnGround = false;
    //             }
    //         }
    //         step = MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION;
    //         break;
    //     }
    //     case MOVE_LEGS_DOWN: {
    //         bool allLegsAreInTheirDefaultPosition = true;
    //         for (leg::FootTargetPosition& leg : targetLegsPositions.legs) {
    //             leg.footOnGround = true;
    //             if (leg.x != 0) {
    //                 allLegsAreInTheirDefaultPosition = false;
    //             }
    //         }
    //         if (allLegsAreInTheirDefaultPosition) {
    //             step = LEGS_IN_DEFAULT_POSITION;
    //         }
    //         else {
    //             step = LIFT_LEGS_IN_INCORRECT_POSITION;
    //         }
    //         break;
    //     }
    //     case LEGS_IN_DEFAULT_POSITION:
    //         return RESULT_LEG_IN_TARGET_POSITION;
    //     default:
    //         printf("ERROR: CaterpillarGait::GoToTheDefaultPosition() - step is undefined\n");
    //         Error_Handler();
    //         return RESULT_UNDEFINED_ERROR;
    //     }

    //     return RESULT_OK;
    // }
    // std::array<float, 2> CaterpillarGait::GetChangingStepValues() {
    //     return { changingStepValues[0], changingStepValues[1] };
    // }

} // namespace logic::gait