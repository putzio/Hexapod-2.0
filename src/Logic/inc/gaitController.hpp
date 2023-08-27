#pragma once

#include <memory>
#include "gaitInterface.hpp"
#include "tripodGait.hpp"
#include "caterpillarGait.hpp"
#include "metachromaticGait.hpp"
#include "Results.h"
#include "Leg.hpp"

namespace logic {
    class GaitController {
    public:
        typedef enum {
            NONE,
            FORWARD,
            BACKWARD,
            TURN_RIGHT,
            TURN_LEFT,
            DEFAULT_POSITION,
            STOP
        } Direction;
    private:
        // std::unique_ptr<gait::GaitInterface> p_ptr_gaitInterface;
        // Direction direction = NONE;
        // std::array<leg::Leg, 6> legs;
        // const leg::LegContainer* targetLegsPositions = nullptr;

        Result GoToPosition(std::array<bool, 6> isGroundDetected);
        Result SetNewTarget();
        
    public:
        std::unique_ptr<gait::GaitInterface> p_ptr_gaitInterface;
        std::array<bool, 6> groundDetectionEnabled = { false, false, false, false, false, false };
        std::array<leg::Leg, 6> legs;
        Direction direction = NONE;
        uint8_t speed = 5;
        const leg::LegContainer* targetLegsPositions = nullptr;
        GaitController();
        Result StandUp();
        Result ChangeDirection(Direction newDirection);
        Result ChangeGait(gait::GaitType newGait);
        Result ChangeSpeed(uint8_t newSpeed);
        Result PeriodicProcess(std::array<bool, 6> isGroundDetected);
        Result ResetLegTargetPositions();
        std::array<leg::ServosPositions, 6> GetSerovAngles();

    };
}

