#pragma once

#include "LegPositionController.hpp"
#include "FootCoordinates.hpp"
#include "LegServos.hpp"
#include "constants.hpp"
#include <memory>

namespace logic::leg {
    class Leg {
    private:
        float servosChangingStep = Constants::DEFAULT_CHANGING_STEP;
        float servosChangingStepOnGround = Constants::DEFAULT_CHANGING_STEP;
        float servosChangingStepInAir = Constants::DEFAULT_CHANGING_STEP;
        FootTargetPosition p_finalTargetPostion = FootTargetPosition(0, true);
    public:
        LegPositionController p_controller;
        LegServos p_servos;

    private:
        bool LegInFinalTargetPosition(const FootCoordinates& coordinates);
        inline void SetCorrectServoChangingStep();

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

        Result SetLegRange(const LegRange& range);

        const FootCoordinates& GetFootCoordinates() const;

        const FootTargetPosition& GetFinalTargetPosition()const;

        Result SetChangingStep(float changingStepOnGround, float changingStepInAir);
        Result SetChangingStep(std::array<float, 2> changingStep);
        float GetChangingStep();
        float GetChangingStepInAir() { return servosChangingStepInAir; };
        float GetChangingStepOnGround() { return servosChangingStepOnGround; };

        LegRange GetRange() const;
    };

}
