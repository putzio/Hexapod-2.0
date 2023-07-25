#include "Leg.hpp"

namespace logic::leg {
    Leg::Leg(Side knee)
        :p_controller(knee),
        p_servos(
            p_controller.CalculateServoPositions(
                p_finalTargetPostion.x.GetCoordinate(),
                p_controller.GetFootOnGroundY().GetCoordinate()
            )) {
        p_controller.SetNewXYPosition(p_finalTargetPostion.x, p_controller.GetLegRange().y[p_finalTargetPostion.footOnGround != 0]);
    };

    Leg::Leg(float upperServoCurrentAngle, float lowerServoCurrentAngle, Side knee)
        :p_controller(upperServoCurrentAngle, lowerServoCurrentAngle, knee),
        p_servos(upperServoCurrentAngle, upperServoCurrentAngle) {
        p_controller.SetNewXYPosition(p_controller.FindXYPosition(p_servos.GetCurrentServoPositions()));
    };

    Result Leg::LegPeriodicProcess() {
        Result r = p_servos.GoToTargetAngle();
        switch (r) {
        case RESULT_SERVO_MOVING:
            return RESULT_LEG_MOVING;
        case RESULT_SERVO_VELOCITY_EQ_0:
            return RESULT_SERVO_VELOCITY_EQ_0;
        case RESULT_SERVO_IN_TARGET_POSITION: {
            if (p_controller.GetCoordinates().x == p_finalTargetPostion.x) {
                return RESULT_LEG_IN_TARGET_POSITION;
            }
            p_controller.FindNextCoordinates(p_finalTargetPostion.x, p_finalTargetPostion.footOnGround);
            MoveJServos();
            return RESULT_LEG_NEW_CONTROLLER_POSITION;
        }
        default:
            return RESULT_UNDEFINED_ERROR;
        }
    }

    inline void Leg::SetCorrectServoChangingStep() {
        if (p_finalTargetPostion.footOnGround) {
            servosChangingStep = servosChangingStepOnGround;
        }
        else {
            servosChangingStep = servosChangingStepInAir;
        }
    }
    Result Leg::MoveJServos() {
        SetCorrectServoChangingStep();
        ServosPositions p = p_controller.CalculateServoPositions();
        return p_servos.SetTargetAngle(p.upperServoAngle, servosChangingStep, p.lowerServoAngle, servosChangingStep);
    }

    Result Leg::MoveJServos(const ServosPositions& positions) {
        SetCorrectServoChangingStep();
        ReturnOnError(p_servos.SetTargetAngle(positions.upperServoAngle, servosChangingStep, positions.lowerServoAngle, servosChangingStep));
        return p_controller.SetNewXYPosition(p_controller.FindXYPosition(positions));
    }

    bool Leg::LegInFinalTargetPosition(const FootCoordinates& coordinates) {//for y?
        return (std::abs((p_finalTargetPostion.x - coordinates.x).GetCoordinate()) < Constants::DELTA_X);
    }

    Result Leg::SetNewTargetPosition(const FootTargetPosition& coordinates) {
        if (!coordinates.x.IsBetween(p_controller.GetLegRange().x)) {
            return RESULT_COORDINATES_OUT_OF_RANGE;
        }
        p_finalTargetPostion = coordinates;
        p_controller.FindNextCoordinates(p_finalTargetPostion.x, p_finalTargetPostion.footOnGround);
        return MoveJServos();
    }

    Result Leg::SetLegRange(const LegRange& range) {
        p_controller.SetLegRange(range);
        return RESULT_OK;
    }



    const FootCoordinates& Leg::GetFootCoordinates() const {
        return p_controller.GetCoordinates();
    }

    const FootTargetPosition& Leg::GetFinalTargetPosition() const {
        return p_finalTargetPostion;
    }

    Result Leg::SetChangingStep(std::array<float, 2> changingStep) {
        return SetChangingStep(changingStep[0], changingStep[1]);
    }

    Result Leg::SetChangingStep(float changingStepOnGround, float changingStepInAir) {
        if (changingStepOnGround > Constants::CHANGING_STEP_RANGE[0] && changingStepOnGround < Constants::CHANGING_STEP_RANGE[1]) {
            this->servosChangingStepOnGround = changingStepOnGround;
        }
        else {
            return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
        }
        if (changingStepInAir > Constants::CHANGING_STEP_RANGE[0] && changingStepInAir < Constants::CHANGING_STEP_RANGE[1]) {
            this->servosChangingStepInAir = changingStepInAir;
            return RESULT_OK;
        }
        return RESULT_SERVO_VELOCITY_OUT_OF_RANGE;
    }

    float Leg::GetChangingStep() {
        return servosChangingStep;
    }

    LegRange Leg::GetRange() const {
        return p_controller.GetLegRange();
    }

}
