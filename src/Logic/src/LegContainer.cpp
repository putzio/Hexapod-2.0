#include "LegContainer.hpp"
#include <cmath>


namespace logic::leg {
    bool LegContainer::operator==(const LegContainer& legContainer)const {
        for (int i = 0; i < 6; i++) {
            if (legContainer.legs[i] != legs[i]) {
                return false;
            }
        }
        return true;
    }
}