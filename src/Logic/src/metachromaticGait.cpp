#include "metachromaticGait.hpp"
#include <stdio.h>
namespace logic::gait {

    MetachromaticGait::MetachromaticGait() {
        step = 0;
        changingStepValues[0] = Constants::DEFAULT_CHANGING_STEP / 3.0;//On ground 
        changingStepValues[1] = Constants::DEFAULT_CHANGING_STEP * 8.0;//In air 
        for (int i = 0; i < 6; i++) {
            xPositions[i] = CalculateXTargetPosition(i);
        }
    };

    void MetachromaticGait::Error_Handler() {
        printf("In Error_Handler()\n");
        while (1) {
            // sleep_ms(1000);
        }
    }
    Result MetachromaticGait::GoForeward() {
        typedef enum {
            LIFT_LEG_AND_MOVE_FORWARD = 0,
            LOWER_LEG_AND_MOVE_IT_BACK_TO_THE_1ST_POSITION = 1,
            MOVE_LEG_BACK_TO_THE_2ND_POSITION = 2,
            MOVE_LEG_BACK_TO_THE_3RD_POSITION = 3,
            MOVE_LEG_BACK_TO_THE_4TH_POSITION = 4,
            MOVE_LEG_BACK_TO_THE_5TH_POSITION = 5
        } FrontLeftLegsSteps;

        switch (step) {
        case LIFT_LEG_AND_MOVE_FORWARD: {
            printf("LIFT_LEG_AND_MOVE_FORWARD\n");
            step = LOWER_LEG_AND_MOVE_IT_BACK_TO_THE_1ST_POSITION;
            break;
        }
        case LOWER_LEG_AND_MOVE_IT_BACK_TO_THE_1ST_POSITION: {
            printf("LOWER_LEG_AND_MOVE_IT_BACK_TO_THE_1ST_POSITION\n");
            step = MOVE_LEG_BACK_TO_THE_2ND_POSITION;
            break;
        }
        case MOVE_LEG_BACK_TO_THE_2ND_POSITION: {
            printf("MOVE_LEG_BACK_TO_THE_2ND_POSITION\n");
            step = MOVE_LEG_BACK_TO_THE_3RD_POSITION;
            break;
        }
        case MOVE_LEG_BACK_TO_THE_3RD_POSITION: {
            printf("MOVE_LEG_BACK_TO_THE_3RD_POSITION\n");
            step = MOVE_LEG_BACK_TO_THE_4TH_POSITION;
            break;
        }
        case MOVE_LEG_BACK_TO_THE_4TH_POSITION: {
            printf("MOVE_LEG_BACK_TO_THE_4TH_POSITION\n");
            step = MOVE_LEG_BACK_TO_THE_5TH_POSITION;
            break;
        }
        case MOVE_LEG_BACK_TO_THE_5TH_POSITION: {
            printf("MOVE_LEG_BACK_TO_THE_5TH_POSITION\n");
            step = LIFT_LEG_AND_MOVE_FORWARD;
            break;
        }
        default:
            printf("ERROR: MetachromaticGait::GoForeward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        for (int i = 0; i < targetLegsPositions.legs.size(); i++) {
                targetLegsPositions.legs[i].x = xPositions[(i + step) % 6];
                if ((i + step) % 6 == LIFT_LEG_AND_MOVE_FORWARD) {
                    targetLegsPositions.legs[i].footOnGround = false;
                }
                else {
                    targetLegsPositions.legs[i].footOnGround = true;
                }
            }
        return RESULT_OK;
    }

    Result MetachromaticGait::GoBackward() {
        typedef enum {
            MOVE_LEG_FOREWARD_TO_THE_0_POSITION = 0,
            MOVE_LEG_FOREWARD_TO_THE_1ST_POSITION = 1,
            MOVE_LEG_FOREWARD_TO_THE_2ND_POSITION = 2,
            MOVE_LEG_FOREWARD_TO_THE_3RD_POSITION = 3,
            MOVE_LEG_FOREWARD_TO_THE_4TH_POSITION = 4,
            LIFT_LEG_AND_MOVE_BACKWARD = 5
        } FrontLeftLegsSteps;

        switch (step) {
        case LIFT_LEG_AND_MOVE_BACKWARD: {
            step = MOVE_LEG_FOREWARD_TO_THE_4TH_POSITION;
            break;
        }
        case MOVE_LEG_FOREWARD_TO_THE_4TH_POSITION: {
            step = MOVE_LEG_FOREWARD_TO_THE_3RD_POSITION;
            break;
        }
        case MOVE_LEG_FOREWARD_TO_THE_3RD_POSITION: {
            step = MOVE_LEG_FOREWARD_TO_THE_2ND_POSITION;
            break;
        }
        case MOVE_LEG_FOREWARD_TO_THE_2ND_POSITION: {
            step = MOVE_LEG_FOREWARD_TO_THE_1ST_POSITION;
            break;
        }
        case MOVE_LEG_FOREWARD_TO_THE_1ST_POSITION: {
            step = MOVE_LEG_FOREWARD_TO_THE_0_POSITION;
            break;
        }
        case MOVE_LEG_FOREWARD_TO_THE_0_POSITION: {
            step = LIFT_LEG_AND_MOVE_BACKWARD;
            break;
        }
        
        default:
            printf("ERROR: MetachromaticGait::GoForeward() - step is undefined\n");
            Error_Handler();
            return RESULT_UNDEFINED_ERROR;
        }
        for (int i = 0; i < targetLegsPositions.legs.size(); i++) {
                targetLegsPositions.legs[i].x = xPositions[(i + step) % 6];
                if ((i + step) % 6 == LIFT_LEG_AND_MOVE_BACKWARD) {
                    targetLegsPositions.legs[i].footOnGround = false;
                }
                else {
                    targetLegsPositions.legs[i].footOnGround = true;
                }
            }
        return RESULT_OK;
    }

    Result MetachromaticGait::TurnRight() { printf("TurnRight\n"); return RESULT_OK; }
    Result MetachromaticGait::TurnLeft() { printf("TurnLeft\n"); return RESULT_OK; }

    leg::SingleCoordinate MetachromaticGait::CalculateXTargetPosition(uint8_t step) {
        const uint8_t numberOfSteps = 6;
        leg::SingleCoordinate xStep = (xForeward - xBackwards) / (numberOfSteps - 1);
        leg::SingleCoordinate result = xForeward - xStep * step;
        if (result < xBackwards) {
            result = xBackwards;
        }
        return result;
    }

    // Result MetachromaticGait::GoToTheDefaultPosition() { printf("GoToTheDefaultPosition\n"); return RESULT_OK; }
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
    //         printf("ERROR: MetachromaticGait::GoToTheDefaultPosition() - step is undefined\n");
    //         Error_Handler();
    //         return RESULT_UNDEFINED_ERROR;
    //     }

    //     return RESULT_OK;
    // }
    // std::array<float, 2> MetachromaticGait::GetChangingStepValues() {
    //     return { changingStepValues[0], changingStepValues[1] };
    // }

} // namespace logic::gait