#include "Logic/Servos_struct.hpp"

void Servos::SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle){
    upperServo.SetTargetAngle(upperServoTargetAngle);
    lowerServo.SetTargetAngle(lowerServoTargetAngle);
}

void Servos::SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep){
    upperServo.SetTargetAngle(upperServoTargetAngle, upperServoAngleChangingStep);
    lowerServo.SetTargetAngle(lowerServoTargetAngle, lowerServoAngleChangingStep);
}

Result Servos::GoToTargetAngle(){
    if(upperServo.GoToTargetAngle() == RESULT_SERVO_IN_TARGET_POSITION && lowerServo.GoToTargetAngle() == RESULT_SERVO_IN_TARGET_POSITION){
        return RESULT_SERVO_IN_TARGET_POSITION;
    }
    return RESULT_SERVO_MOVING;
}

ServosPositions Servos::GetCurrentServoPositions(){
    ServosPositions servos;
    servos.lowerServoAngle = lowerServo.GetCurrentAngle();
    servos.upperServoAngle = upperServo.GetCurrentAngle();
}