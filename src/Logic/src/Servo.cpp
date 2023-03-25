#include "../inc/Servo.hpp"
#include <cmath>
// #include"../include/constants.hpp"

Servo::Servo(float currentAngle) {
    p_currentAngle = currentAngle;
}

Result Servo::GoToTargetAngle() {
    if (std::abs(p_currentAngle - p_targetAngle) < p_angleChangingStep) {
        p_currentAngle = p_targetAngle;
        return RESULT_SERVO_IN_TARGET_POSITION;
    }

    if (std::abs(p_angleChangingStep) < Constants::PI / 1800.0f) {
        return RESULT_SERVO_VELOCITY_EQ_0;
    }

    if (p_currentAngle < p_targetAngle) {
        p_currentAngle += p_angleChangingStep;
    }
    else {
        p_currentAngle -= p_angleChangingStep;
    }
    return RESULT_SERVO_MOVING;
}

void Servo::SetTargetAngle(const float targetAngle) {
    if (targetAngle > Constants::ANGLE_RANGE[0] && targetAngle < Constants::ANGLE_RANGE[1]) {
        p_targetAngle = targetAngle;
    }
}
void Servo::SetTargetAngle(float targetAngle, float angleChangingStep) {
    SetTargetAngle(targetAngle);

    if (angleChangingStep > Constants::PI / 600 && angleChangingStep < Constants::PI / 48) {
        p_angleChangingStep = angleChangingStep;
    }
}
void Servo::SetCurrentAngle(float angle) {
    if (angle < Constants::ANGLE_RANGE[0] || angle > Constants::ANGLE_RANGE[1])
        return;
    else
        p_currentAngle = angle;
}

const float Servo::GetCurrentAngle()const {
    return p_currentAngle;
}
const float Servo::GetTargetAngle()const {
    return p_targetAngle;
}
const float Servo::GetAngleChangingStep()const {
    return p_angleChangingStep;
}