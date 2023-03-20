#include "../inc/LegPositionControllerInterface.hpp"


LegPositionControllerInterface::LegPositionControllerInterface(float x, float y, Side knee) {
    if (knee == Side::KNEE_FRONT) {
        calculateServoPositionsPtr = CalculateServoPositions_KneeFront;
    }
    else {
        calculateServoPositionsPtr = CalculateServoPositions_KneeBack;
    }
    p_coordinates.x = x;
    p_coordinates.y = y;
}
LegPositionControllerInterface::LegPositionControllerInterface(FootCoordinates coordinates, Side knee) {
    LegPositionControllerInterface(coordinates.x, coordinates.y, knee);
}

float LegPositionControllerInterface::CalculateYPosition(const float& xPos) {
    if (p_legRange.x[0] > xPos || p_legRange.x[1] < xPos) {
        return -1;
    }
    float xMapped = MapXInRange(xPos);
    p_coordinates.y = (1.0 - sin(xMapped * 3.1415)) * (double)(p_legRange.y[1] - p_legRange.y[0]) + p_legRange.y[0];
    return p_coordinates.y;
}

float LegPositionControllerInterface::MapXInRange(const float& xPos) {
    return (xPos - p_legRange.x[0]) / (p_legRange.x[1] - p_legRange.x[0]);
}

ServosPositions LegPositionControllerInterface::CalculateServoPositions_KneeFront(float xNew, float yNew) {
    ServosPositions servosPositions;
    //p_coordinates.x = xNew; p_coordinates.y = yNew;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
    float gamma = acos((2 - dSquared) / 2);
    float alpha = atan2(yNew, xNew) - (Constants::PI - gamma) / 2;

    servosPositions.upperServoAngle = Constants::PI - alpha;
    servosPositions.lowerServoAngle = gamma - (Constants::PI / 2.0);

    return servosPositions;
}

ServosPositions LegPositionControllerInterface::CalculateServoPositions_KneeBack(float xNew, float yNew) {
    ServosPositions servosPositions;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
    float gamma = acos((2.0f - dSquared) / 2.0f);
    float alpha = -atan2(yNew, xNew) + (Constants::PI + gamma) / 2;

    servosPositions.upperServoAngle = alpha;
    servosPositions.lowerServoAngle = Constants::PI - gamma;

    return servosPositions;
}

FootCoordinates LegPositionControllerInterface::FindNextCoordinates(const float& xTarget, const bool& footOnGround) {
    if (xTarget - p_coordinates.x < Constants::DELTA_X) {
        p_coordinates.x = xTarget;
    }
    else if (xTarget < p_coordinates.x) {
        p_coordinates.x -= Constants::DELTA_X;
    }
    else {
        p_coordinates.x += Constants::DELTA_X;
    }

    if (!footOnGround) {
        p_coordinates.y = CalculateYPosition(p_coordinates.x);
    }
    else {
        p_coordinates.y = p_legRange.y[1];
    }
    return p_coordinates;
}


FootCoordinates LegPositionControllerInterface::FindNextCoordinates(const FootTargetPosition& target) {
    return FindNextCoordinates(target.x, target.footOnGround);
}

float LegPositionControllerInterface::GetX() {
    return p_coordinates.x;
}
float LegPositionControllerInterface::GetY() {
    return p_coordinates.y;
}

const FootCoordinates& LegPositionControllerInterface::GetCoordinates() const {
    return p_coordinates;
}
const LegRange& LegPositionControllerInterface::GetLegRange() const {
    return p_legRange;
}

void LegPositionControllerInterface::SetNewXYPosition(float xNew, float yNew) {
    SetX(xNew);
    SetY(yNew);
}

void LegPositionControllerInterface::SetNewXYPosition(const FootCoordinates& coordinates) {
    SetNewXYPosition(coordinates.x, coordinates.y);
}

FootCoordinates LegPositionControllerInterface::FindXYPosition(const ServosPositions& positions) {
    FootCoordinates coordinates;

    coordinates.x = (sin(positions.upperServoAngle - Constants::PI / 2) - sin(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));
    coordinates.y = (cos(positions.upperServoAngle - Constants::PI / 2) + cos(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));

    SetNewXYPosition(coordinates);
    return coordinates;
}

void LegPositionControllerInterface::SetX(float xNew) {
    if (xNew < p_legRange.x[0] && xNew > p_legRange.x[1]) {
        return;
    }
    p_coordinates.x = xNew;
}
void LegPositionControllerInterface::SetY(float yNew) {
    if (yNew < p_legRange.y[0] && yNew > p_legRange.y[1]) {
        return;
    }
    p_coordinates.y = yNew;
}

ServosPositions LegPositionControllerInterface::CalculateServoPositions(float xNew, float yNew) {
    return (this->*calculateServoPositionsPtr)(xNew, yNew);
}

ServosPositions LegPositionControllerInterface::CalculateServoPositions(const FootCoordinates& coordinates) {
    return CalculateServoPositions(coordinates.x, coordinates.y);
}

ServosPositions LegPositionControllerInterface::CalculateServoPositions() {
    return CalculateServoPositions(p_coordinates);
}