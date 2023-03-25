#include "../inc/walkingInterface.hpp"

Result WalkingInterface::GoForeward() {
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
}
Result WalkingInterface::GoBackward() {
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
}
Result WalkingInterface::TurnRight() {
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
}
Result WalkingInterface::TurnLeft() {
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
}
Result WalkingInterface::GoToTheDefaultPosition() {
    for (auto leg : targetLegsPositions->legs) {
        leg.footOnGround = false;
        leg.x = 0;
    }
    return RESULT_OK;
}

WalkingInterface::Mode WalkingInterface::GetWalkingMode() {
    return NONE;
}
const LegContainer* WalkingInterface::GetTargetLegsPositionsPtr() {
    return targetLegsPositions;
}