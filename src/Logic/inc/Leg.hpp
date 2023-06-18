#pragma once

#include "LegPositionController.hpp"
#include "FootCoordinates.hpp"
#include "LegServos.hpp"
#include "..\..\..\include\constants.hpp"
#include <memory>

namespace logic::leg {
    class Leg {
    private:
        float servosChangingStep = Constants::PI * 1.0 / 180.0f;

        FootTargetPosition p_finalTargetPostion = FootTargetPosition(0, true);
    public:
        LegPositionController p_controller;
        LegServos p_servos;

    private:
        bool LegInFinalTargetPosition(const FootCoordinates& coordinates);


    public:
        Leg(Side knee = Side::KNEE_BACK);
        Leg(float upperServoCurrentAngle, float lowerServoCurrentAngle, Side knee = Side::KNEE_BACK);
        // Leg(LegServos& servos, LegPositionController& controller);

        Result LegPeriodicProcess();
        /**
         * @brief Set the New Target Position for leg
         * and optionally calculate coordinates from mm (devide by LEG_LENGTH)
         *
         * @param coordinates new coordinates
         * @return Result if the new target position was set correctly
         */

        Result SetNewTargetPosition(const FootTargetPosition& coordinates);
        Result SetNewTargetPosition(const FootCoordinates& coordinates);
        /**
         * @brief Set the New Target Position for Servos
         * The position controller does not calculate the steps on a way to it
         * @param coordinates new coordinates
         * @return Result if the new target position was set correctly
         */
        Result MoveJServos();
        Result MoveJServos(const ServosPositions& positions);

        const FootCoordinates& GetFootCoordinates() const;

        const FootTargetPosition& GetFinalTargetPosition()const;

        void SetChangingStep(float changingStep);
        float GetChangingStep();
    };

}
