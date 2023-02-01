#pragma once

#include "Logic/Servo.hpp"
#include "Logic/LegPositionControllerInterface.hpp"

typedef struct LegServos
{
    Servo upperServo;
    Servo lowerServo;
    void SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle);
    void SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep);

    Result GoToTargetAngle();
    ServosPositions GetCurrentServoPositions();
}LegServos;