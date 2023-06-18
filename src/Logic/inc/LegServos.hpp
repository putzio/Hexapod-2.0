#pragma once

#include "Servo.hpp"
#include "LegPositionController.hpp"

namespace logic::leg {
    typedef struct LegServos {
    private:
        Servo upperServo;
        Servo lowerServo;

    public:
        LegServos(float upperServoCurrentAngle = Constants::PI / 2, float lowerServoCurrentAngle = Constants::PI / 2)
            :upperServo(upperServoCurrentAngle),
            lowerServo(lowerServoCurrentAngle) {
        };
        LegServos(ServosPositions startingPositions)
            :upperServo(startingPositions.upperServoAngle),
            lowerServo(startingPositions.lowerServoAngle) {
        };
        void SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle);
        void SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep);

        Result GoToTargetAngle();
        ServosPositions GetCurrentServoPositions();
    }LegServos;
}