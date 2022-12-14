#include "Logic/Servo.hpp"
#include <cmath>
#include"constants.hpp"

Servo::Servo(float currentAngle){
p_currentAngle = currentAngle;
}

void Servo::GoToTargetAngle(){
    if(std::abs(p_currentAngle - p_targetAngle) < p_angleChangingStep)
        return;
    if(p_currentAngle < p_targetAngle){
        p_currentAngle += p_angleChangingStep;
    }
    else{
        p_currentAngle -= p_angleChangingStep;
    }
}

void Servo::SetTargetAngle(float targetAngle){
    if(targetAngle > Constants::ANGLE_RANGE[0] && targetAngle < Constants::ANGLE_RANGE[1]){
        p_targetAngle = targetAngle;
    }
}
void Servo::SetTargetAngle(float targetAngle, float angleChangingStep){
    SetTargetAngle(targetAngle);

    if(angleChangingStep > Constants::PI / 600 && angleChangingStep < Constants::PI / 48){
        p_angleChangingStep = angleChangingStep;
    }
}
void Servo::SetServoAngle(float angle){
    if(angle < Constants::ANGLE_RANGE[0] || angle > Constants::ANGLE_RANGE[1])
        return;
    else
        p_currentAngle = angle;
}


const uint16_t Servo::GetServoAngleInMs()const{
    uint16_t msValue;
    //map the angle value in the angle range
    msValue = (p_currentAngle - Constants::ANGLE_RANGE[0]) / (Constants::ANGLE_RANGE[1] - Constants::ANGLE_RANGE[0])
    //multiply by the ms range
    * (Constants::ANGLE_RANGE_MS[1] - Constants::ANGLE_RANGE_MS[0])
    //and add the minimum value
    + Constants::ANGLE_RANGE_MS[0];

    return msValue;
}


const float Servo::GetServoAngle()const{
    return p_currentAngle;
}
const float Servo::GetTargetAngle()const{
    return p_targetAngle;
}
const float Servo::GetAngleChangingStep()const{
    return p_angleChangingStep;
}