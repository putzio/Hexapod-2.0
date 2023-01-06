#include "Logic/WalkingModes/walkingInterface.hpp"

 Result WalkingInterface::GoForeward(){
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
 }
 Result WalkingInterface::GoBackward(){
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
 }
 Result WalkingInterface::TurnRight(){
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
 }
 Result WalkingInterface::TurnLeft(){
    return RESULT_WRONG_WALKING_INTERFACE_MODE;
 }
Result WalkingInterface::GoToTheDefaultPosition(){
    for(SimplifiedLeg leg : targetLegsPositions->legs){
        leg.legUp = false;
        leg.x = 0;
    }
    return RESULT_OK;
}

WalkingInterface::Mode WalkingInterface::GetWalkingMode(){
    return NONE;
}
const LegContainer *WalkingInterface::GetTargetLegsPositionsPtr(){
    return targetLegsPositions;
}