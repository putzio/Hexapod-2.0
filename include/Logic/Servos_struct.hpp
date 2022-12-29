#pragma once

#include "Logic/Servo.hpp"

typedef struct Servos
{
    Servo upperServo;
    Servo lowerServo;
    void SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle);
    void SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep);

    void GoToTargetAngle();
}Servos;