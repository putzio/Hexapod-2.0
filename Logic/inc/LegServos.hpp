#pragma once

#include "Servo.hpp"
#include "LegPositionControllerInterface.hpp"

typedef struct LegServos {
private:
    Servo upperServo;
    Servo lowerServo;

public:
    void SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle);
    void SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep);

    Result GoToTargetAngle();
    ServosPositions GetCurrentServoPositions();
}LegServos;