#pragma once

#include <memory>
#include "gaitInterface.hpp"
#include "Results.h"
#include "Leg.hpp"

namespace logic {
    class GaitController {
        typedef enum {
            NONE,
            FOREWARD,
            BACKWARD,
            TURN_RIGHT,
            TURN_LEFT,
            DEFAULT_POSITION
        } Direction;
    private:
        std::unique_ptr<gait::GaitInterface> p_ptr_gaitInterface;
        Direction direction = NONE;
        std::array<leg::Leg, 6> legs;
        const leg::LegContainer* targetLegsPositions = nullptr;

        Result GoToPosition();
        Result SetNewTarget();
    public:
        GaitController();
        Result ChangeDirection(Direction newDirection);
        Result ChangeGait(gait::GaitInterface::Gait newGait);
        Result PeriodicProcess();
    };
}