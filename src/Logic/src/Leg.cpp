#include "Leg.hpp"
#include <stdio.h>

namespace logic::leg {
    Leg::Leg(Side knee)
        :m_controller(knee),
        m_servos(
            m_controller.CalculateServoPositions(
                m_finalTargetPostion.x.GetCoordinate(),
                m_controller.GetFootOnGroundY().GetCoordinate()
            )) {
        m_controller.SetNewXYPosition(m_finalTargetPostion.x, m_controller.GetLegRange().y[m_finalTargetPostion.footOnGround != 0]);
    };

    Leg::Leg(float upperServoCurrentAngle, float lowerServoCurrentAngle, Side knee)
        :m_controller(upperServoCurrentAngle, lowerServoCurrentAngle, knee),
        m_servos(upperServoCurrentAngle, upperServoCurrentAngle) {
        m_controller.SetNewXYPosition(m_controller.FindXYPosition(m_servos.GetCurrentServoPositions()));
    };

    bool Leg::HasLegReachedHalfOfRange() const {
        return (std::abs(m_controller.GetCoordinates().x.GetCoordinate() - m_finalTargetPostion.x.GetCoordinate()) * 2.0) < 
        (m_controller.GetLegRange().x[1].GetCoordinate() - m_controller.GetLegRange().x[0].GetCoordinate());
    }

    Result Leg::LegPeriodicProcess() {
        if (m_isGroundDetectionEnabled) {
            // printf("Leg::LegPeriodicProcess\n");
            printf("> upper: %f\n", m_servos.GetCurrentServoPositions().upperServoAngle);
            printf("> lower: %f\n", m_servos.GetCurrentServoPositions().lowerServoAngle);
            printf("> upper target: %f\n", m_servos.GetTargetServoPositions().upperServoAngle);
            printf("> lower target: %f\n", m_servos.GetTargetServoPositions().lowerServoAngle);
            printf("> x: %f\n", m_controller.GetCoordinates().GetX_mm());
            printf("> x_target: %f\n", m_finalTargetPostion.x.GetCoordinate_mm());
            printf("> m_detectingGround: %d\n", m_detectingGround);
        }
        Result r = m_servos.GoToTargetAngles();
        switch (r) {
        case RESULT_SERVO_MOVING:
            return RESULT_LEG_MOVING;
        case RESULT_SERVO_VELOCITY_EQ_0:
            return RESULT_SERVO_VELOCITY_EQ_0;
        case RESULT_SERVO_IN_TARGET_POSITION: {
            if (m_controller.GetCoordinates().x == m_finalTargetPostion.x) {
                if (!m_isGroundDetectionEnabled || m_finalTargetPostion.footOnGround || m_detectingGround || !HasLegReachedHalfOfRange()) {
                    m_detectingGround = false;
                    return RESULT_LEG_IN_TARGET_POSITION;
                }
                printf("> SetGroundDetecingPosition: %d\n", SetGroundDetecingPosition());
                m_detectingGround = true;
                return RESULT_LEG_NEW_CONTROLLER_POSITION;
            }
            printf("> NEW_CONTROLLER_POSITION: %f\n", m_servos.GetCurrentServoPositions().upperServoAngle);
            m_controller.FindNextCoordinates(m_finalTargetPostion.x, m_finalTargetPostion.footOnGround);
            MoveJServos();
            return RESULT_LEG_NEW_CONTROLLER_POSITION;
        }
        default:
            return RESULT_UNDEFINED_ERROR;
        }
    }

    Result Leg::PeriodicProcessWithGroundDetection(bool isGroundDetected) {
        if (!m_isGroundDetectionEnabled) {
            return LegPeriodicProcess();
        }

        if (isGroundDetected && m_detectingGround) {
            m_controller.SetCurrentHightAsFootHightOnGround(m_servos.GetCurrentServoPositions());
            FootTargetPosition newTargetPosition;

            //Set new target position depending on current position (front/back)
            if (m_controller.GetCoordinates().x < 0) {
                newTargetPosition.x = m_controller.GetLegRange().x[0];
            }
            else {
                newTargetPosition.x = m_controller.GetLegRange().x[1];
            }
            newTargetPosition.footOnGround = true;

            SetNewTargetPosition(newTargetPosition);
            m_controller.FindNextCoordinates(m_finalTargetPostion.x, m_finalTargetPostion.footOnGround);
            MoveJServos();
        }
        Result r = LegPeriodicProcess();
        printf("> r: %d\n", r);
        return r;
    }

    Result Leg::JustGoToTarget() {
        return m_servos.GoToTargetAngles();
    }

    inline void Leg::SetCorrectServoChangingStep() {
        if (m_finalTargetPostion.footOnGround) {
            m_servosChangingStep = m_servosChangingStepOnGround;
        }
        else {
            m_servosChangingStep = m_servosChangingStepInAir;
        }
    }
    Result Leg::MoveJServos() {
        SetCorrectServoChangingStep();
        ServosPositions p = m_controller.CalculateServoPositions();
        return m_servos.SetTargetAngle(p.upperServoAngle, m_servosChangingStep, p.lowerServoAngle, m_servosChangingStep);
    }

    Result Leg::MoveJServos(const ServosPositions& positions) {
        SetCorrectServoChangingStep();
        ReturnOnError(m_servos.SetTargetAngle(positions.upperServoAngle, m_servosChangingStep, positions.lowerServoAngle, m_servosChangingStep));
        return m_controller.SetNewXYPosition(m_controller.FindXYPosition(positions));
    }

    bool Leg::LegInFinalTargetPosition(const FootCoordinates& coordinates) {//for y?
        return (std::abs((m_finalTargetPostion.x - coordinates.x).GetCoordinate()) < Constants::DELTA_X);
    }

    Result Leg::SetNewTargetPosition(const FootTargetPosition& coordinates) {
        // if (!coordinates.x.IsBetween(m_controller.GetLegRange().x)) {
        // return RESULT_COORDINATES_OUT_OF_RANGE;
        // }
        m_finalTargetPostion = coordinates;
        m_controller.FindNextCoordinates(m_finalTargetPostion.x, m_finalTargetPostion.footOnGround);
        return MoveJServos();
    }

    Result Leg::SetLegRange(const LegRange& range) {
        m_controller.SetLegRange(range);
        return RESULT_OK;
    }
    void Leg::SetGroundDetection(bool isGroundDetectionEnabled) {
        m_isGroundDetectionEnabled = isGroundDetectionEnabled;
    }

    // Result Leg::StandUp(){

    // }

    const FootCoordinates& Leg::GetFootCoordinates() const {
        return m_controller.GetCoordinates();
    }

    const FootTargetPosition& Leg::GetFinalTargetPosition() const {
        return m_finalTargetPostion;
    }

    Result Leg::SetChangingStep(std::array<float, 2> changingStep, uint8_t speed) {
        return SetChangingStep(changingStep[0] * (0.5 + speed / 10.0), changingStep[1] * (0.5 + speed / 10.0));
    }

    Result Leg::SetChangingStep(float changingStepOnGround, float changingStepInAir) {
        if (changingStepOnGround > Constants::CHANGING_STEP_RANGE[0] && changingStepOnGround < Constants::CHANGING_STEP_RANGE[1]) {
            this->m_servosChangingStepOnGround = changingStepOnGround;
        }
        else {
            return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
        }
        if (changingStepInAir > Constants::CHANGING_STEP_RANGE[0] && changingStepInAir < Constants::CHANGING_STEP_RANGE[1]) {
            this->m_servosChangingStepInAir = changingStepInAir;
            return RESULT_OK;
        }
        return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
    }

    float Leg::GetChangingStep() {
        return m_servosChangingStep;
    }

    LegRange Leg::GetRange() const {
        return m_controller.GetLegRange();
    }
    Result Leg::SetGroundDetecingPosition() {
        if (m_controller.GetCoordinates().x < 0) {
            return m_servos.SetTargetAngle(Constants::PI * 80.0 / 180.0, m_servosChangingStepInAir, Constants::PI / 2.0, m_servosChangingStepInAir);
        }
        return m_servos.SetTargetAngle(Constants::PI * 100.0 / 180.0, m_servosChangingStepInAir, Constants::PI / 2.0, m_servosChangingStepInAir);
    }

}
