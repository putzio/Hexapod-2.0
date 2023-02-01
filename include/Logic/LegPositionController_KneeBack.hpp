#pragma once

#include "LegPositionControllerInterface.hpp"

class LegPositionController_KneeBack: public LegPositionControllerInterface {
public:
    LegPositionController_KneeBack();
    LegPositionController_KneeBack(float xPos, float yPos);
    ServosPositions CalculateServoPositions(float xNew, float yNew) override;
    ServosPositions CalculateServoPositions(const FootCoordinates& coordinates) override;
    ServosPositions CalculateServoPositions() override;
};