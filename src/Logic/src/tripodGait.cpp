#include "tripodGait.hpp"
#include <stdio.h>
namespace logic::gait {
    void TripodGait::Error_Handler() {
        printf("In Error_Handler()\n");
        while (1) {
            // sleep_ms(1000);
        }
    }
    Result TripodGait::GoForeward() {
        typedef enum {
            LIFT_LEGS_AND_MOVE_THEM_FORWARD,
            LOWER_LEGS_AND_MOVE_THEM_BACKWARD
        } FirstGroupOfLegsSteps;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_THEM_FORWARD: {
            printf("LIFT_LEGS_AND_MOVE_THEM_FORWARD\n");
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LOWER_LEGS_AND_MOVE_THEM_BACKWARD;
            printf("after 1st case, step = %d\n", step);
            break;
        }
        case LOWER_LEGS_AND_MOVE_THEM_BACKWARD: {
            printf("LOWER_LEGS_AND_MOVE_THEM_BACKWARD\n");
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
        default:
            printf("ERROR: TripodGait::GoForeward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        if (step == 2) {
            printf("step == 2\n");
            Error_Handler();
        }
        return RESULT_OK;
    }

    Result TripodGait::GoBackward() {
        typedef enum {
            LIFT_LEGS_AND_MOVE_THEM_BACKWARD,
            LOWER_LEGS_MOVE_THEM_FORWARD
        } FirstGroupOfLegsSteps;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_THEM_BACKWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            step = LOWER_LEGS_MOVE_THEM_FORWARD;
            break;
        }
        case LOWER_LEGS_MOVE_THEM_FORWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].x = xForeward;
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].x = xBackwards;
                targetLegsPositions.legs[i].footOnGround = false;
            }
            step = LIFT_LEGS_AND_MOVE_THEM_BACKWARD;
            break;
        }
        default:
            printf("ERROR: TripodGait::GoBackward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

    Result TripodGait::TurnLeft() {
        typedef enum {
            LIFT_LEGS_AND_MOVE_BACKWARDS,
            LOWER_LEG_AND_MOVE_FORWARD
        } frontLeftLegSteps;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_BACKWARDS: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : leftLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xBackwards;
                else
                    targetLegsPositions.legs[i].x = xForeward;
            }
            for (int i : rightLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xForeward;
                else
                    targetLegsPositions.legs[i].x = xBackwards;
            }
            step = LOWER_LEG_AND_MOVE_FORWARD;
            break;
        }
        case LOWER_LEG_AND_MOVE_FORWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : leftLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xForeward;
                else
                    targetLegsPositions.legs[i].x = xBackwards;
            }
            for (int i : rightLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xBackwards;
                else
                    targetLegsPositions.legs[i].x = xForeward;
            }
            step = LIFT_LEGS_AND_MOVE_BACKWARDS;
            break;
        }
        default:
            printf("ERROR: TripodGait::TurnLeft() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

    Result TripodGait::TurnRight() {
        typedef enum {
            LIFT_LEGS_AND_MOVE_FORWARD,
            LOWER_LEG_AND_MOVE_BACKWARDS
        } frontLeftLegSteps;
        switch (step) {
        case LIFT_LEGS_AND_MOVE_FORWARD: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : leftLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xForeward;
                else
                    targetLegsPositions.legs[i].x = xBackwards;
            }
            for (int i : rightLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xBackwards;
                else
                    targetLegsPositions.legs[i].x = xForeward;
            }
            step = LOWER_LEG_AND_MOVE_BACKWARDS;
            break;
        }
        case LOWER_LEG_AND_MOVE_BACKWARDS: {
            for (int i : firstGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = true;
            }
            for (int i : secondGroupOfLegs) {
                targetLegsPositions.legs[i].footOnGround = false;
            }
            for (int i : leftLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xBackwards;
                else
                    targetLegsPositions.legs[i].x = xForeward;
            }
            for (int i : rightLegs) {
                if (targetLegsPositions.legs[i].footOnGround)
                    targetLegsPositions.legs[i].x = xForeward;
                else
                    targetLegsPositions.legs[i].x = xBackwards;
            }
            step = LIFT_LEGS_AND_MOVE_FORWARD;
            break;
        }
        default:
            printf("ERROR: TripodGait::TurnRight() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        return RESULT_OK;
    }

    // Result TripodGait::GoToTheDefaultPosition() {
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
    //         printf("ERROR: TripodGait::GoToTheDefaultPosition() - step is undefined\n");
    //         Error_Handler();
    //         return RESULT_UNDEFINED_ERROR;
    //     }

    //     return RESULT_OK;
    // }

} // namespace logic::gait