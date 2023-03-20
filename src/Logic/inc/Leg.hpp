#pragma once

#include "LegPositionControllerInterface.hpp"
#include "FootCoordinates.hpp"
#include "LegServos.hpp"
#include "..\..\..\include\constants.hpp"
#include <memory>

class Leg {
private:

    LegPositionControllerInterface p_controller;
    FootTargetPosition p_finalTargetPostion = FootTargetPosition(0, true);
    bool LegInFinalTargetPosition(const FootCoordinates& coordinates);

public:
    LegServos p_servos;
    Leg(Side knee = Side::KNEE_BACK):p_controller(knee) {};
    Leg(LegServos& servos, LegPositionControllerInterface& controller);

    Result LegPeriodicProcess();   //TEst???
    void MoveLegToTheXYTarget(const ServosPositions* positions = nullptr);

    /**
     * @brief Set the New Target Position for leg
     * and calculate coordinates from mm (devide by LEG_LENGTH)
     *
     * @param coordinates new coordinates
     * @return Result if the new target position was set correctly
     */
    Result SetNewTargetPosition(const FootTargetPosition& coordinates);
    Result SetNewTargetPosition(const FootCoordinates& coordinates);
    const FootTargetPosition& GetFootCoordinates() const;
};