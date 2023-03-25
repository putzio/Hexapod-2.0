#include "../inc/tripodWalk.hpp"
// #include "../Logic/inc/Leg.hpp"
// #include "../include/constants.hpp"

extern float g_xCurrentRange[2];

void TripodWalk::SetPositionBackDown(LegContainer& legContainer) {
    legContainer.legs[LegContainer::LEFT_FRONT].SetCoordinates(g_xCurrentRange[0], false);
    legContainer.legs[LegContainer::RIGHT_FRONT].SetCoordinates(g_xCurrentRange[1], true);
    legContainer.legs[LegContainer::LEFT_MIDDLE].SetCoordinates(g_xCurrentRange[1], true);
    legContainer.legs[LegContainer::RIGHT_MIDDLE].SetCoordinates(g_xCurrentRange[0], false);
    legContainer.legs[LegContainer::LEFT_BACK].SetCoordinates(g_xCurrentRange[0], false);
    legContainer.legs[LegContainer::RIGHT_BACK].SetCoordinates(g_xCurrentRange[1], true);
}
void TripodWalk::SetPositionBackUp(LegContainer& legContainer) {
    legContainer.legs[LegContainer::LEFT_FRONT].SetCoordinates(g_xCurrentRange[0], true);
    legContainer.legs[LegContainer::RIGHT_FRONT].SetCoordinates(g_xCurrentRange[1], false);
    legContainer.legs[LegContainer::LEFT_MIDDLE].SetCoordinates(g_xCurrentRange[1], false);
    legContainer.legs[LegContainer::RIGHT_MIDDLE].SetCoordinates(g_xCurrentRange[0], true);
    legContainer.legs[LegContainer::LEFT_BACK].SetCoordinates(g_xCurrentRange[0], true);
    legContainer.legs[LegContainer::RIGHT_BACK].SetCoordinates(g_xCurrentRange[1], false);
}
void TripodWalk::SetPositionFrontUp(LegContainer& legContainer) {
    legContainer.legs[LegContainer::LEFT_FRONT].SetCoordinates(g_xCurrentRange[1], true);
    legContainer.legs[LegContainer::RIGHT_FRONT].SetCoordinates(g_xCurrentRange[0], false);
    legContainer.legs[LegContainer::LEFT_MIDDLE].SetCoordinates(g_xCurrentRange[0], false);
    legContainer.legs[LegContainer::RIGHT_MIDDLE].SetCoordinates(g_xCurrentRange[1], true);
    legContainer.legs[LegContainer::LEFT_BACK].SetCoordinates(g_xCurrentRange[1], true);
    legContainer.legs[LegContainer::RIGHT_BACK].SetCoordinates(g_xCurrentRange[0], false);
}
void TripodWalk::SetPositionFrontDown(LegContainer& legContainer) {
    legContainer.legs[LegContainer::LEFT_FRONT].SetCoordinates(g_xCurrentRange[1], false);
    legContainer.legs[LegContainer::RIGHT_FRONT].SetCoordinates(g_xCurrentRange[0], true);
    legContainer.legs[LegContainer::LEFT_MIDDLE].SetCoordinates(g_xCurrentRange[0], true);
    legContainer.legs[LegContainer::RIGHT_MIDDLE].SetCoordinates(g_xCurrentRange[1], false);
    legContainer.legs[LegContainer::LEFT_BACK].SetCoordinates(g_xCurrentRange[1], false);
    legContainer.legs[LegContainer::RIGHT_BACK].SetCoordinates(g_xCurrentRange[0], true);
}

LegContainer TripodWalk::ReturnSetPosition(void (TripodWalk::* SetPositionFunctionPtr)(LegContainer&)) {
    LegContainer leg;
    (this->*SetPositionFunctionPtr)(leg);
    return leg;
}

TripodWalk::TripodWalk() {
    ;
}

Result TripodWalk::GoForeward() {
    switch (step) {
    case 0:
        // *targetLegsPositions = ReturnSetPosition(SetPositionBackDown);
        step++;
        break;

    case 1:
        // *targetLegsPositions = ReturnSetPosition(SetPositionFrontDown);
        step--;
        break;
    default:
        break;
    }
}
Result TripodWalk::GoBackward() {}
Result TripodWalk::TurnRight() {}
Result TripodWalk::TurnLeft() {}

WalkingInterface::Mode TripodWalk::GetWalkingMode() {
    return TRIPOD_WALK;
}


// Result TripodWalk::GoToPosition(){
//     switch (step)
//     {
//     case 0:
//         targetLegsPositions = &p_positions[0];
//         step++;
//         break;

//     case 1:
//         if(currentLegsCoordinates)
//         break;
//     case 2:
//         targetLegsPositions = &p_positions[1];
//         break;

//     default:
//         break;
//     }
//     return RESULT_OK;
// }