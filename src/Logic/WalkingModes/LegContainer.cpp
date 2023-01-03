#include "Logic/WalkingModes/LegContainer.hpp"
#include <cmath>
// #include "global.hpp"

extern float g_yCurrentRange[2];

bool SimplifiedLeg::operator==(const SimplifiedLeg &leg)const{
    return (leg.legUp == this->legUp) && std::abs(leg.x - this->x) < 0.1;
}
bool SimplifiedLeg::operator!=(const SimplifiedLeg &leg)const{
    return !(leg == *this);
}
bool SimplifiedLeg::operator==(const Coordinates &leg)const{
    if(this->legUp && g_yCurrentRange[1] - leg.y < 0.01){
        return false;
    }
    if(!this->legUp && g_yCurrentRange[1] - leg.y > 0.1){
        return false;
    }
    return std::abs(leg.x - this->x) < 0;
}




bool LegContainer::operator==(const LegContainer &legContainer)const{
        for(int i = 0; i < 6; i++){
            if(legContainer.legs[i] != legs[i]){
                return false;
            }
        }
        return true;
    }