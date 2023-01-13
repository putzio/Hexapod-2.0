#pragma once

#include "Logic/Servo.hpp"
#include "Logic/LegPositionController.hpp"

typedef struct Servos
{
    Servo upperServo;
    Servo lowerServo;
    void SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle);
    void SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep);

    Result GoToTargetAngle();
    ServosPositions GetCurrentServoPositions();
}Servos;