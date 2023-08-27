#pragma once

#include "LegPositionController.hpp"
#include "FootCoordinates.hpp"
#include "LegServos.hpp"
#include "constants.hpp"
#include <memory>
#include <cmath>

namespace logic::leg {
    class Leg {
    private:
        float m_servosChangingStep = Constants::DEFAULT_CHANGING_STEP;
        float m_servosChangingStepOnGround = Constants::DEFAULT_CHANGING_STEP;
        float m_servosChangingStepInAir = Constants::DEFAULT_CHANGING_STEP;
        FootTargetPosition m_finalTargetPostion = FootTargetPosition(0, true);
        bool m_detectingGround = false;

    public:
        LegPositionController m_controller;
        LegServos m_servos;

    private:
        bool LegInFinalTargetPosition(const FootCoordinates& coordinates);
        inline void SetCorrectServoChangingStep();
        Result SetGroundDetecingPosition();
        bool HasLegReachedHalfOfRange()const;

    public:
        bool m_isGroundDetectionEnabled = false;
        Leg(Side knee = Side::KNEE_BACK);
        Leg(float upperServoCurrentAngle, float lowerServoCurrentAngle, Side knee = Side::KNEE_BACK);
        // Leg(LegServos& servos, LegPositionController& controller);

        Result LegPeriodicProcess();
        Result PeriodicProcessWithGroundDetection(bool isGroundDetected);
        Result JustGoToTarget();
        /**
         * @brief Set the New Target Position for leg
         * and optionally calculate coordinates from mm (devide by LEG_LENGTH)
         *
         * @param coordinates new coordinates
         * @return Result if the new target position was set correctly
         */

        Result SetNewTargetPosition(const FootTargetPosition& coordinates);
        Result SetNewTargetPosition(const FootCoordinates& coordinates);
        Result StandUp();
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
        Result SetChangingStep(std::array<float, 2> changingStep, uint8_t speed);
        void SetGroundDetection(bool isGroundDetectionEnabled);
        float GetChangingStep();
        float GetChangingStepInAir() { return m_servosChangingStepInAir; };
        float GetChangingStepOnGround() { return m_servosChangingStepOnGround; };

        LegRange GetRange() const;
    };

}
