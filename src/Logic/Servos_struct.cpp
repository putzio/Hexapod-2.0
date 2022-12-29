#include "Logic/Servos_struct.hpp"

void Servos::SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle){
    upperServo.SetTargetAngle(upperServoTargetAngle);
    lowerServo.SetTargetAngle(lowerServoTargetAngle);
}

void Servos::SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep){
    upperServo.SetTargetAngle(upperServoTargetAngle, upperServoAngleChangingStep);
    lowerServo.SetTargetAngle(lowerServoTargetAngle, lowerServoAngleChangingStep);
}

void Servos::GoToTargetAngle(){
    upperServo.GoToTargetAngle();
    lowerServo.GoToTargetAngle();
}