#include "../inc/LegServos.hpp"

void LegServos::SetTargetAngle(float upperServoTargetAngle, float lowerServoTargetAngle) {
    upperServo.SetTargetAngle(upperServoTargetAngle);
    lowerServo.SetTargetAngle(lowerServoTargetAngle);
}

void LegServos::SetTargetAngle(float upperServoTargetAngle, float upperServoAngleChangingStep, float lowerServoTargetAngle, float lowerServoAngleChangingStep) {
    upperServo.SetTargetAngle(upperServoTargetAngle, upperServoAngleChangingStep);
    lowerServo.SetTargetAngle(lowerServoTargetAngle, lowerServoAngleChangingStep);
}

Result LegServos::GoToTargetAngle() {
    if (upperServo.GoToTargetAngle() == RESULT_SERVO_IN_TARGET_POSITION && lowerServo.GoToTargetAngle() == RESULT_SERVO_IN_TARGET_POSITION) {
        return RESULT_SERVO_IN_TARGET_POSITION;
    }
    return RESULT_SERVO_MOVING;
}

ServosPositions LegServos::GetCurrentServoPositions() {
    ServosPositions servos;
    servos.lowerServoAngle = lowerServo.GetCurrentAngle();
    servos.upperServoAngle = upperServo.GetCurrentAngle();
    return servos;
}