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
        //[rad / period] e.g. PI / 180 means that servo will move max 1 degree in a single period (GoToTargetAngle() call)
        float p_angleChangingStep = 0;

    public:
        Servo(float currentAngle = DEFAULT_SERVO_ANGLE);

        Result GoToTargetAngle();

        Result SetTargetAngle(float targetAngle);
        Result SetTargetAngle(float targetAngle, float angleChangingStep);
        Result SetCurrentAngle(float servoAngle);
        Result SetAngleChangingStep(float angleChangingStep);

        const float GetCurrentAngle()const;
        const float GetTargetAngle()const;
        const float GetAngleChangingStep()const;
    };
}