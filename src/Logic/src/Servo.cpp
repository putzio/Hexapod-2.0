#include "Servo.hpp"

namespace logic::leg {
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

    Result Servo::SetTargetAngle(const float targetAngle) {
        if (targetAngle > Constants::ANGLE_RANGE[0] && targetAngle < Constants::ANGLE_RANGE[1]) {
            p_targetAngle = targetAngle;
            return RESULT_OK;
        }
        return RESULT_SERVO_ANGLE_OUT_OF_RANGE;
    }
    Result Servo::SetTargetAngle(float targetAngle, float angleChangingStep) {
        ReturnOnError(SetTargetAngle(targetAngle));

        if (angleChangingStep > Constants::PI / 600.0 && angleChangingStep < Constants::PI / 48.0) {
            p_angleChangingStep = angleChangingStep;
            return RESULT_OK;
        }
        return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
    }
    Result Servo::SetCurrentAngle(float angle) {
        if (angle < Constants::ANGLE_RANGE[0] || angle > Constants::ANGLE_RANGE[1]) {
            return RESULT_SERVO_ANGLE_OUT_OF_RANGE;
        }
        else
            p_currentAngle = angle;
        return RESULT_OK;
    }

    Result Servo::SetAngleChangingStep(float angleChangingStep) {
        if (angleChangingStep > Constants::PI / 1800.0 && angleChangingStep < Constants::PI / 48.0) {
            p_angleChangingStep = angleChangingStep;
            return RESULT_OK;
        }
        return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
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
}