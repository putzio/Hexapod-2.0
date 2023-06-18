#pragma once
#include "gaitInterface.hpp"

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
    }
} // namespace logic::gait