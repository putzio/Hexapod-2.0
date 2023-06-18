#pragma once
#include "gaitInterface.hpp"
#include "constants.hpp"

namespace logic::gait {
    class TripodGait : public GaitInterface {
    public:
        TripodGait();
        Result GoForeward() override;
        Result GoBackward() override;
        Result TurnRight() override;
        Result TurnLeft() override;
        Result GoToTheDefaultPosition() override;
        Gait GetCurrentGait() override { return TRIPOD_WALK; };
    private:
        typedef enum {
            MOVE_LIFTED_LEGS_TO_THE_DEFAULT_X_POSITION,
            LIFT_LEGS_IN_INCORRECT_POSITION,
            MOVE_LEGS_DOWN,
            LEGS_IN_DEFAULT_POSITION
        }DefaultPositionSteps;
        float xForeward = Constants::X_ABSOLUTE_RANGE[0];
        float xBackwards = Constants::X_ABSOLUTE_RANGE[1];
        uint8_t firstGroupOfLegs[3] = {
            leg::LegContainer::LEFT_FRONT,
            leg::LegContainer::RIGHT_MIDDLE,
            leg::LegContainer::LEFT_BACK
        };
        uint8_t secondGroupOfLegs[3] = {
            leg::LegContainer::RIGHT_FRONT,
            leg::LegContainer::LEFT_MIDDLE,
            leg::LegContainer::RIGHT_BACK
        };
    };
} // namespace logic::gait