#pragma once
#include "stdint.h"
#include "constants.hpp"

#define DEFAULT_SERVO_ANGLE (Constants::PI / 2.0)

class Servo{
    private:
    float p_currentAngle;
    float p_targetAngle;
    //defines how far can the servo move in a single GoToTargetAngle() mthod call
    float p_angleChangingStep;

    public:
    Servo(float currentAngle = DEFAULT_SERVO_ANGLE);

    void GoToTargetAngle();

    void SetTargetAngle(float targetAngle);
    void SetTargetAngle(float targetAngle, float angleChangingStep);
    void SetServoAngle(float servoAngle);

    const float GetServoAngle()const;
    const float GetTargetAngle()const;
    const float GetAngleChangingStep()const;

    const uint16_t GetServoAngleInMs()const;
};