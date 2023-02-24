#pragma once

#include "LegPositionControllerInterface.hpp"

class LegPositionController_KneeFront: public LegPositionControllerInterface {
public:
    LegPositionController_KneeFront();
    LegPositionController_KneeFront(float xPos, float yPos);
    ServosPositions CalculateServoPositions(float xNew, float yNew) override;
    ServosPositions CalculateServoPositions(const FootCoordinates& coordinates) override;
    ServosPositions CalculateServoPositions() override;
};