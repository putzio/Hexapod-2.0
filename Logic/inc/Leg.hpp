#pragma once

#include "LegPositionControllerInterface.hpp"
#include "LegPositionController_KneeFront.hpp"
#include "LegPositionController_KneeBack.hpp"
#include "LegServos.hpp"
#include "../../include/constants.hpp"
#include <memory>

typedef enum Side:uint8_t {
    UNDEFINED,
    KNEE_BACK,
    KNEE_FRONT
}Side;

class Leg {
private:

    std::unique_ptr<LegPositionControllerInterface> p_controller;
    FootTargetPosition p_finalTargetPostion;

    bool LegInFinalTargetPosition(const FootCoordinates& coordinates);
    void MoveLegToTheXYTarget();

public:
    LegServos p_servos;
    Leg(Side knee = Side::KNEE_BACK);
    Leg(LegServos& servos, LegPositionControllerInterface& controller);

    Result LegPeriodicProcess();   //TEst???

    /**
     * @brief Set the New Target Position for leg
     * and calculate coordinates from mm (devide by LEG_LENGTH)
     *
     * @param coordinates new coordinates
     * @return Result if the new target position was set correctly
     */
    Result SetNewTargetPosition(const FootTargetPosition& coordinates);

    const FootTargetPosition& GetFootCoordinates() const;
};