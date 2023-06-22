#pragma once
#include "stdint.h"
#include "constants.hpp"
#include "Results.h"

#define DEFAULT_SERVO_ANGLE (Constants::PI / 2.0)

namespace logic::leg {
    class Servo {
    private:
        float p_currentAngle;
        float p_targetAngle;
        //defines how far can the servo move in a single GoToTargetAngle() mthod call
        float p_angleChangingStep;

    public:
        Servo(float currentAngle = DEFAULT_SERVO_ANGLE);

        Result GoToTargetAngle();

        Result SetTargetAngle(float targetAngle);
        Result SetTargetAngle(float targetAngle, float angleChangingStep);
        Result SetCurrentAngle(float servoAngle);

        const float GetCurrentAngle()const;
        const float GetTargetAngle()const;
        const float GetAngleChangingStep()const;
    };
}