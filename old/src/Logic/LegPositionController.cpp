#include "Logic/LegPositionControllerInterface.hpp"

LegPositionController::LegPositionController(){
    y = (sin(60.0*PI/180.0) * 20000.0);
    x=0;
}

LegPositionController::LegPositionController(int16_t xPos, uint16_t yPos){
    SetNewXYPosition(xPos, yPos);
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

ServosPositions LegPositionController::CalculateServoPositions(int16_t xNew, uint16_t yNew){
    ServosPositions servosPositions;
    //x = xNew; y = yNew;
    float dSquared = pow(xNew / 10000.0, 2) + pow(yNew / 10000.0, 2);
    float gamma = acos((2-dSquared)/2);
    float alpha;
    if(xNew == 0){
        alpha =  gamma/2;
    }
    else{
        alpha = atan((double)yNew/(double)xNew) - (PI - gamma)/2;
    }    

    servosPositions.UpperServoAngle = PI - alpha;
    servosPositions.LowerServoAngle = gamma - (PI / 2.0);

    return servosPositions;
}

int16_t LegPositionController::GetX(){
    return x;
}
uint16_t LegPositionController::GetY(){
    return y;
}

void LegPositionController::SetNewXYPosition(int16_t xNew, uint16_t yNew){
    SetX(xNew);
    SetY(yNew);
}

void LegPositionController::FindXYPosition(const ServosPositions& positions){
    x = (sin(positions.UpperServoAngle - PI / 2) - sin(PI - positions.UpperServoAngle - positions.LowerServoAngle)) * 10000 + 0.5;
    y = (cos(positions.UpperServoAngle - PI / 2) + cos(PI - positions.UpperServoAngle - positions.LowerServoAngle)) * 10000 + 0.5;
}

void LegPositionController::SetX(int16_t xNew){
    if(xNew < xRange[0] && xNew > xRange[1]){
        return;
    }
    x = xNew;
}
void LegPositionController::SetY(uint16_t yNew){
    if(yNew < yRange[0] && yNew > yRange[1]){
        return;
    }
    y = yNew;
}