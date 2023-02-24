#include "LegPositionController_KneeFront.hpp"

LegPositionController_KneeFront::LegPositionController_KneeFront() {
    SetNewXYPosition(0, Constants::DEFAULT_LEG_HIGHT);
}
LegPositionController_KneeFront::LegPositionController_KneeFront(float xPos, float yPos) {
    SetNewXYPosition(xPos, yPos);
}

ServosPositions LegPositionController_KneeFront::CalculateServoPositions(float xNew, float yNew) {
    ServosPositions servosPositions;
    //p_coordinates.x = xNew; p_coordinates.y = yNew;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
    float gamma = acos((2 - dSquared) / 2);
    float alpha;
    if (xNew == 0) {
        alpha = gamma / 2;
    }
    else {
        alpha = atan((double)yNew / (double)xNew) - (Constants::PI - gamma) / 2;
    }

    servosPositions.upperServoAngle = Constants::PI - alpha;
    servosPositions.lowerServoAngle = gamma - (Constants::PI / 2.0);

    return servosPositions;
}
ServosPositions LegPositionController_KneeFront::CalculateServoPositions(const FootCoordinates& coordinates) {
    return CalculateServoPositions(coordinates.x, coordinates.y);
}

ServosPositions LegPositionController_KneeFront::CalculateServoPositions() {
    return CalculateServoPositions(p_coordinates);
}