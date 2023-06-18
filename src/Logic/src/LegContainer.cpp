#include "../inc/LegContainer.hpp"
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

    // bool LegContainer::operator==(const LegsCoordinates& legCoordinates)const {
    //     return LegContainerEqualsToCoordinates(legCoordinates);
    // }

    // bool LegContainer::LegContainerEqualsToCoordinates(const LegsCoordinates& legCoordinates)const {
    //     for (int i = 0; i < 6; i++) {
    //         if (this->legs[i] != legCoordinates.coordinates[i]) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
}