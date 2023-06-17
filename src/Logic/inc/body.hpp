#pragma once
#include "Leg.hpp"

namespace logic {
    class Body {
    protected:
        leg::Leg legs[6];
    public:
        Body();
    };
}