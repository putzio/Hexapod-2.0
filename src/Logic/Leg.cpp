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

void Leg::LegPeriodicProcess(){
    p_servos.GoToTargetAngle();
}

const Servos* const Leg::GetServosPtr()const{
    return &p_servos;
}