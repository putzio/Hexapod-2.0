#pragma once

#include "../../WalkingModes/inc/walkingInterface.hpp"
#include <memory>
#include "../../include/Results.h"

class MoveController {
private:
    std::unique_ptr<WalkingInterface> p_ptr_walkingInterface;
    Result SetNewTarget();
    Result MoveToTarget();
public:

    Result MoveControllerPeriodicProcess();
};
