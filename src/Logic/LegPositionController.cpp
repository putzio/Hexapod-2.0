#include "Logic/LegPositionController.hpp"

LegPositionController::LegPositionController(){
    y = (sin(60.0*PI/180.0) * 2.0);
    x=0;
}

LegPositionController::LegPositionController(float xPos, float yPos){
    SetNewXYPosition(xPos, yPos);
}

void LegPositionController::CalculateYPosition(const float &xPos){
    if(xRange[0] > xPos || xRange[1] < xPos)
        return;
    else{
        float xMapped = MapXInRange(xPos);
        y = (1.0 - sin(xMapped * 3.1415)) * (double)(yRange[1] - yRange[0]) + yRange[0];
    }
}

float LegPositionController::MapXInRange(const float &xPos){
    return (xPos - xRange[0]) / (xRange[1] - xRange[0]);
}

ServosPositions LegPositionController::CalculateServoPositions(float xNew, float yNew){
    ServosPositions servosPositions;
    //x = xNew; y = yNew;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
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

float LegPositionController::GetX(){
    return x;
}
float LegPositionController::GetY(){
    return y;
}

void LegPositionController::SetNewXYPosition(float xNew, float yNew){
    SetX(xNew);
    SetY(yNew);
}

void LegPositionController::FindXYPosition(const ServosPositions& positions){
    x = (sin(positions.UpperServoAngle - PI / 2) - sin(PI - positions.UpperServoAngle - positions.LowerServoAngle));
    y = (cos(positions.UpperServoAngle - PI / 2) + cos(PI - positions.UpperServoAngle - positions.LowerServoAngle));
}

void LegPositionController::SetX(float xNew){
    if(xNew < xRange[0] && xNew > xRange[1]){
        return;
    }
    x = xNew;
}
void LegPositionController::SetY(float yNew){
    if(yNew < yRange[0] && yNew > yRange[1]){
        return;
    }
    y = yNew;
}