#include "Logic/Leg.hpp"

Leg::Leg(Side side, Side elbow){
    p_side = side;
    p_elbow = elbow;
}

Leg::Leg(Side side, Side elbow, Servos &servos, LegPositionController &controller){
    Leg(side, elbow);
    // p_controller = LegPositionController(controller);
    // p_servos = Servos(servos);
}

void Leg::MoveLegToTheXYTarget(const Coordinates &coordinates){
    Coordinates rawCoordinates;
    rawCoordinates.x = coordinates.x / (double) Constants::LEG_LENGTH;
    rawCoordinates.y = coordinates.y / (double) Constants::LEG_LENGTH;
    ServosPositions positions = p_controller.CalculateServoPositions(rawCoordinates);
    p_servos.SetTargetAngle(positions.upperServoAngle, positions.lowerServoAngle);
}

Coordinates Leg::CalculateNewCoordinates(Coordinates &coordinates){
    if(p_finalTargetPostion.x < coordinates.x){
        coordinates.x =- Constants::DELTA_X;
    }
    else{
        coordinates.x =+ Constants::DELTA_X;
    }
    if(!p_legUp){
        coordinates.y = p_controller.yRange[1];
        return coordinates;
    }
    coordinates.y = p_controller.CalculateYPosition(coordinates.x);
    return coordinates;
}

Result Leg::LegPeriodicProcess(){
    if(p_servos.GoToTargetAngle() != RESULT_SERVO_IN_TARGET_POSITION){
        return RESULT_LEG_MOVING;
    }
    Coordinates coordinates = p_controller.FindXYPosition(p_servos.GetCurrentServoPositions());

    if(LegInFinalTargetPosition(coordinates)){
        return RESULT_LEG_IN_TARGET_POSITION;
    }
    
    CalculateNewCoordinates(coordinates);
    MoveLegToTheXYTarget(coordinates);
    return RESULT_LEG_NEW_CONTROLLER_POSITION;
    
}

void Leg::SetNewTargetPosition(const Coordinates &coordinates, bool legUp){
    p_finalTargetPostion = coordinates;
    p_legUp = legUp;
}

const Servos* const Leg::GetServosPtr()const{
    return &p_servos;
}

bool Leg::LegInFinalTargetPosition(const Coordinates &coordinates){
    return (std::abs(p_finalTargetPostion.x - coordinates.x) < Constants::DELTA_X);
}