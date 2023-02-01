#pragma once
#include "stdint.h"
#include "constants.hpp"
#include "Results.h"

#define DEFAULT_SERVO_ANGLE (Constants::PI / 2.0)

class Servo{
    private:
    float p_currentAngle;
    float p_targetAngle;
    //defines how far can the servo move in a single GoToTargetAngle() mthod call
    float p_angleChangingStep;

    public:
    Servo(float currentAngle = DEFAULT_SERVO_ANGLE);

    Result GoToTargetAngle();

    void SetTargetAngle(float targetAngle);
    void SetTargetAngle(float targetAngle, float angleChangingStep);
    void SetCurrentAngle(float servoAngle);

    const float GetCurrentAngle()const;
    const float GetTargetAngle()const;
    const float GetAngleChangingStep()const;
};