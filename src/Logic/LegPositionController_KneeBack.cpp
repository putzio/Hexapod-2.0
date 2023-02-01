#include "Logic/LegPositionController_KneeBack.hpp"

LegPositionController_KneeBack::LegPositionController_KneeBack() {
    SetNewXYPosition(0, Constants::DEFAULT_LEG_HIGHT);
}
LegPositionController_KneeBack::LegPositionController_KneeBack(float xPos, float yPos) {
    SetNewXYPosition(xPos, yPos);
}

ServosPositions LegPositionController_KneeBack::CalculateServoPositions(float xNew, float yNew) {
    ServosPositions servosPositions;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
    float gamma = acos((2 - dSquared) / 2);
    float alpha_plus_beta;
    if (xNew == 0) {
        alpha_plus_beta = Constants::PI / 2;
    }
    else {
        alpha_plus_beta = atan((double)yNew / (double)xNew) + Constants::PI - gamma / 2;
    }

    servosPositions.upperServoAngle = Constants::PI - alpha_plus_beta;
    servosPositions.lowerServoAngle = (3.0 * Constants::PI / 2.0) - gamma;

    return servosPositions;
}
ServosPositions LegPositionController_KneeBack::CalculateServoPositions(const FootCoordinates& coordinates) {
    return CalculateServoPositions(coordinates.x, coordinates.y);
}

ServosPositions LegPositionController_KneeBack::CalculateServoPositions() {
    return CalculateServoPositions(p_coordinates);
}