#pragma once

// #include "../../WalkingModes/inc/walkingInterface.hpp"
#include <memory>
#include "..\..\..\include\Results.h"

namespace logic {
    class MoveController {
    private:
        // std::unique_ptr<GaitInterface> p_ptr_walkingInterface;
        Result SetNewTarget();
        Result MoveToTarget();
    public:

        Result MoveControllerPeriodicProcess();
    };
}