#include "Logic/WalkingModes/walkingInterface.hpp"

WalkingInterface::Mode WalkingInterface::GetWalkingMode(){
    return NONE;
}
const LegContainer *WalkingInterface::GetTargetLegsPositionsPtr(){
    return targetLegsPositions;
}

Result WalkingInterface::GoToPosition(){return RESULT_WRONG_WALKING_INTERFACE_MODE;}