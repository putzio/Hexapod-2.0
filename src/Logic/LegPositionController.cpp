#include "Logic/LegPositionController.hpp"

LegPositionController::LegPositionController(){
    y = (sin(60.0*PI/180.0) * 20000.0);
    x=0;
}

LegPositionController::LegPositionController(int16_t xPos, uint16_t yPos){
    y = yPos;
    x = xPos;
}

int16_t LegPositionController::GetX(){
    return x;
}
uint16_t LegPositionController::GetY(){
    return y;
}

void LegPositionController::CalculateYPosition(const int16_t &xPos){
    if(xRange[0] > xPos || xRange[1] < xPos)
        return;
    else{
        uint16_t xMapped = MapXInRange(xPos);
        y = (1.0 - sin(xMapped * 3.1415/10000.0)) * (double)(yRange[1] - yRange[0]) + yRange[0] + 0.5;
    }
}

uint16_t LegPositionController::MapXInRange(const int16_t &xPos){
    return (xPos - xRange[0]) * 10000 / (xRange[1] - xRange[0]);
}

ServosPositions LegPositionController::CalculateServoPositions(int16_t newX, uint16_t newY){
    ServosPositions servosPositions;
    //x = xNew; y = yNew;
    float dSquared = pow(newX / 10000.0, 2) + pow(newY / 10000.0, 2);
    float gamma = acos((2-dSquared)/2);
    float alpha;
    if(newX == 0){
        alpha =  gamma/2;
    }
    else{
        alpha = atan((double)newY/(double)newX) - (PI - gamma)/2;
    }    

    servosPositions.UpperServoAngle = PI - alpha;
    servosPositions.LowerServoAngle = gamma - (PI / 2.0);

    return servosPositions;
}
