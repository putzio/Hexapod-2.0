#pragma once
#include "constants.h"
#include "stdint.h"

#define DEFAULT_SERVO_ANGLE (PI/2.0)

class Servo{
    private:
    float p_currentAngle;
    float p_targetAngle;
    //defines how far can the servo move in a single GoToTargetAngle() mthod call
    float p_angleChangingStep;

    public:
    const float ANGLE_RANGE [2] = {0, PI};
    const uint16_t ANGLE_RANGE_MS[2] = {500, 2500};

    public:
    Servo(float currentAngle = DEFAULT_SERVO_ANGLE);

    void GoToTargetAngle();

    void SetTargetAngle(float targetAngle);
    void SetTargetAngle(float targetAngle, float angleChangingStep);
    void SetServoAngle(float servoAngle);

    const float GetServoAngle();
    const float GetTargetAngle();
    const float GetAngleChangingStep();

    uint16_t GetServoAngleInMs();
};