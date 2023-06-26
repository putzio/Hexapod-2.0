#include "LegServos.hpp"

namespace logic::leg {

    Result LegServos::SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep) {
        ReturnOnError(upperServo.SetTargetAngle(upperServoTargetAngle, upperServoAngleChangingStep));
        return (lowerServo.SetTargetAngle(lowerServoTargetAngle, lowerServoAngleChangingStep));
    }

    Result LegServos::GoToTargetAngle() {
        Result upperResult = upperServo.GoToTargetAngle();
        Result lowerResult = lowerServo.GoToTargetAngle();
        if (upperResult == RESULT_SERVO_IN_TARGET_POSITION && lowerResult == RESULT_SERVO_IN_TARGET_POSITION) {
            return RESULT_SERVO_IN_TARGET_POSITION;
        }
        if (upperResult == RESULT_SERVO_VELOCITY_EQ_0 || lowerResult == RESULT_SERVO_VELOCITY_EQ_0) {
            return RESULT_SERVO_VELOCITY_EQ_0;
        }
        return RESULT_SERVO_MOVING;
    }

    ServosPositions LegServos::GetCurrentServoPositions() {
        ServosPositions servos;
        servos.lowerServoAngle = lowerServo.GetCurrentAngle();
        servos.upperServoAngle = upperServo.GetCurrentAngle();
        return servos;
    }
}