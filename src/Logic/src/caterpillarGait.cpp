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
                targetLegsPositions.legs[i] = liftAndForeward;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = lowerAndBackward;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY: {
            printf("LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_HALFWAY\n");
            for (int i : frontLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = lowerAndBackward;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = liftAndForeward;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY: {
            printf("LOWER_FRONT_LEGS_AND_MOVE_THEM_BACKWARD_FULLY\n");
            for (int i : frontLegs) {
                targetLegsPositions.legs[i] = lowerAndBackward;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = liftAndForeward;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
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
                targetLegsPositions.legs[i] = liftAndBackward;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = lowerAndForeward;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_HALFWAY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_HALFWAY: {
            for (int i : frontLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = lowerAndForeward;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = liftAndBackward;
            }
            step = LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_FULLY;
            break;
        }
        case LOWER_FRONT_LEGS_AND_MOVE_THEM_FORWARD_FULLY: {
            for (int i : frontLegs) {
                targetLegsPositions.legs[i] = lowerAndForeward;
            }
            for (int i : middleLegs) {
                targetLegsPositions.legs[i] = liftAndBackward;
            }
            for (int i : backLegs) {
                targetLegsPositions.legs[i] = lowerAndHalfway;
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

    Result CaterpillarGait::TurnRight() {
        printf("TurnRight\n");
        typedef enum {
            LIFT_LEG_AND_MOVE_FORWARD,
            LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY,
            LOWER_LEG_AND_MOVE_BACKWARD_FULLY
        } FrontLeftLegsSteps;
        namespace l = leg;
        switch (step) {
        case LIFT_LEG_AND_MOVE_FORWARD: {
            targetLegsPositions.legs[l::LegContainer::LEFT_FRONT] = liftAndForeward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_FRONT] = lowerAndForeward;
            targetLegsPositions.legs[l::LegContainer::LEFT_MIDDLE] = lowerAndHalfway;
            targetLegsPositions.legs[l::LegContainer::RIGHT_MIDDLE] = liftAndBackward;
            targetLegsPositions.legs[l::LegContainer::LEFT_BACK] = lowerAndBackward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_BACK] = lowerAndHalfway;
            step = LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY;
            break;
        }
        case LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY: {
            targetLegsPositions.legs[l::LegContainer::LEFT_FRONT] = lowerAndHalfway;
            targetLegsPositions.legs[l::LegContainer::RIGHT_FRONT] = liftAndBackward;
            targetLegsPositions.legs[l::LegContainer::LEFT_MIDDLE] = lowerAndBackward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_MIDDLE] = lowerAndHalfway;
            targetLegsPositions.legs[l::LegContainer::LEFT_BACK] = liftAndForeward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_BACK] = lowerAndForeward;
            step = LOWER_LEG_AND_MOVE_BACKWARD_FULLY;
            break;
        }
        case LOWER_LEG_AND_MOVE_BACKWARD_FULLY: {
            targetLegsPositions.legs[l::LegContainer::LEFT_FRONT] = lowerAndBackward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_FRONT] = lowerAndHalfway;
            targetLegsPositions.legs[l::LegContainer::LEFT_MIDDLE] = liftAndForeward;
            targetLegsPositions.legs[l::LegContainer::RIGHT_MIDDLE] = lowerAndForeward;
            targetLegsPositions.legs[l::LegContainer::LEFT_BACK] = lowerAndHalfway;
            targetLegsPositions.legs[l::LegContainer::RIGHT_BACK] = liftAndBackward;
            step = LIFT_LEG_AND_MOVE_FORWARD;
            break;
        }
        }
        return RESULT_OK;
    }
    Result CaterpillarGait::TurnLeft() {
        printf("TurnLeft\n");
        typedef enum {
            LIFT_LEG_AND_MOVE_BACKWARD,
            LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY,
            LOWER_LEG_AND_MOVE_FORWARD_FULLY,
        } FrontLeftLegsSteps;
        switch (step) {
        case LIFT_LEG_AND_MOVE_BACKWARD: {
            targetLegsPositions.legs[leg::LegContainer::LEFT_FRONT] = liftAndBackward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_FRONT] = lowerAndHalfway;
            targetLegsPositions.legs[leg::LegContainer::LEFT_MIDDLE] = lowerAndForeward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_MIDDLE] = liftAndForeward;
            targetLegsPositions.legs[leg::LegContainer::LEFT_BACK] = lowerAndHalfway;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_BACK] = lowerAndBackward;
            step = LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY;
            break;
        }
        case LOWER_LEG_AND_MOVE_BACKWARD_HALFWAY: {
            targetLegsPositions.legs[leg::LegContainer::LEFT_FRONT] = lowerAndHalfway;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_FRONT] = lowerAndBackward;
            targetLegsPositions.legs[leg::LegContainer::LEFT_MIDDLE] = liftAndBackward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_MIDDLE] = lowerAndHalfway;
            targetLegsPositions.legs[leg::LegContainer::LEFT_BACK] = lowerAndForeward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_BACK] = liftAndForeward;
            step = LOWER_LEG_AND_MOVE_FORWARD_FULLY;
            break;
        }
        case LOWER_LEG_AND_MOVE_FORWARD_FULLY: {
            targetLegsPositions.legs[leg::LegContainer::LEFT_FRONT] = lowerAndForeward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_FRONT] = liftAndForeward;
            targetLegsPositions.legs[leg::LegContainer::LEFT_MIDDLE] = lowerAndHalfway;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_MIDDLE] = lowerAndBackward;
            targetLegsPositions.legs[leg::LegContainer::LEFT_BACK] = liftAndBackward;
            targetLegsPositions.legs[leg::LegContainer::RIGHT_BACK] = lowerAndHalfway;
            step = LIFT_LEG_AND_MOVE_BACKWARD;
            break;
        }
        }
        return RESULT_OK;
    }


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