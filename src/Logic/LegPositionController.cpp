#include "Logic/LegPositionController.hpp"

LegPositionController::LegPositionController(){
    xRange[0] = Constants::X_ABSOLUTE_RANGE[0];
    xRange[1] = Constants::X_ABSOLUTE_RANGE[1];
    yRange[0] = Constants::Y_ABSOLUTE_RANGE[0];
    yRange[1] = Constants::Y_ABSOLUTE_RANGE[1];

    p_coordinates.y = (sin(60.0* Constants::PI/180.0) * 2.0);
    p_coordinates.x=0;
}

LegPositionController::LegPositionController(float xPos, float yPos){
    xRange[0] = Constants::X_ABSOLUTE_RANGE[0];
    xRange[1] = Constants::X_ABSOLUTE_RANGE[1];
    yRange[0] = Constants::Y_ABSOLUTE_RANGE[0];
    yRange[1] = Constants::Y_ABSOLUTE_RANGE[1];
    SetNewXYPosition(xPos, yPos);
}

float LegPositionController::CalculateYPosition(const float &xPos){
    if(xRange[0] > xPos || xRange[1] < xPos){
        return -1;
    }
    float xMapped = MapXInRange(xPos);
    p_coordinates.y = (1.0 - sin(xMapped * 3.1415)) * (double)(yRange[1] - yRange[0]) + yRange[0];
    return p_coordinates.y;
}

float LegPositionController::MapXInRange(const float &xPos){
    return (xPos - xRange[0]) / (xRange[1] - xRange[0]);
}

ServosPositions LegPositionController::CalculateServoPositions(float xNew, float yNew){
    ServosPositions servosPositions;
    //p_coordinates.x = xNew; p_coordinates.y = yNew;
    float dSquared = pow(xNew, 2) + pow(yNew, 2);
    float gamma = acos((2-dSquared)/2);
    float alpha;
    if(xNew == 0){
        alpha =  gamma/2;
    }
    else{
        alpha = atan((double)yNew/(double)xNew) - (Constants::PI - gamma)/2;
    }    

    servosPositions.upperServoAngle = Constants::PI - alpha;
    servosPositions.lowerServoAngle = gamma - (Constants::PI / 2.0);

    return servosPositions;
}
ServosPositions LegPositionController::CalculateServoPositions(const Coordinates &coordinates){
    return CalculateServoPositions(coordinates.x, coordinates.y);
}

float LegPositionController::GetX(){
    return p_coordinates.x;
}
float LegPositionController::GetY(){
    return p_coordinates.y;
}

Coordinates LegPositionController::GetCoordinates(){
    return p_coordinates;
}

void LegPositionController::SetNewXYPosition(float xNew, float yNew){
    SetX(xNew);
    SetY(yNew);
}

void LegPositionController::SetNewXYPosition(const Coordinates &coordinates){
    SetNewXYPosition(coordinates.x, coordinates.y);
}

Coordinates LegPositionController::FindXYPosition(const ServosPositions& positions){
    Coordinates coordinates;
    
    coordinates.x = (sin(positions.upperServoAngle - Constants::PI / 2) - sin(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));
    coordinates.y = (cos(positions.upperServoAngle - Constants::PI / 2) + cos(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));

    SetNewXYPosition(coordinates);
    return coordinates;
}

void LegPositionController::SetX(float xNew){
    if(xNew < xRange[0] && xNew > xRange[1]){
        return;
    }
    p_coordinates.x = xNew;
}
void LegPositionController::SetY(float yNew){
    if(yNew < yRange[0] && yNew > yRange[1]){
        return;
    }
    p_coordinates.y = yNew;
}