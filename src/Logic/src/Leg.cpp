#include "../inc/Leg.hpp"


Leg::Leg(Side knee)
    :p_controller(knee),
    p_servos(
        p_controller.CalculateServoPositions(
            p_finalTargetPostion.x.GetCoordinate(),
            p_controller.GetLegRange().y[1]
        )) {
    p_controller.SetNewXYPosition(p_finalTargetPostion.x, p_controller.GetLegRange().y[p_finalTargetPostion.footOnGround != 0]);
};

Leg::Leg(float upperServoCurrentAngle, float lowerServoCurrentAngle, Side knee)
    :p_controller(knee),
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

Result Leg::MoveJServos() {
    ServosPositions p = p_controller.CalculateServoPositions();
    p_servos.SetTargetAngle(p.upperServoAngle, servosChangingStep, p.lowerServoAngle, servosChangingStep);
    return RESULT_OK;
}

Result Leg::MoveJServos(const ServosPositions& positions) {
    p_servos.SetTargetAngle(positions.upperServoAngle, servosChangingStep, positions.lowerServoAngle, servosChangingStep);
    p_controller.SetNewXYPosition(p_controller.FindXYPosition(positions));
    return RESULT_OK;
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
// Result Leg::SetNewTargetPosition(const FootCoordinates& coordinates) {
//     if ((coordinates.x < p_controller.GetLegRange().x[0] || coordinates.x > p_controller.GetLegRange().x[1])
//         || coordinates.y < p_controller.GetLegRange().y[0] || coordinates.y > p_controller.GetLegRange().y[1]) {
//         return RESULT_COORDINATES_OUT_OF_RANGE;
//     }
//     p_finalTargetPostion = coordinates;
//     p_controller.SetNewXYPosition(coordinates);
//     return RESULT_OK;
// }

// Result Leg::SetNewTargetPosition_mm(const FootTargetPosition& coordinates) {
//     return SetNewTargetPosition(coordinates);
// }
// Result Leg::SetNewTargetPosition_mm(const FootCoordinates& coordinates) {
//     FootCoordinates newCoordinates = coordinates;
//     newCoordinates /= (float)Constants::LEG_LENGTH;
//     return SetNewTargetPosition(newCoordinates);
// }


const FootCoordinates& Leg::GetFootCoordinates() const {
    return p_controller.GetCoordinates();
}

const FootTargetPosition& Leg::GetFinalTargetPosition() const {
    return p_finalTargetPostion;
}

void Leg::SetChangingStep(float changingStep) {
    if (changingStep > Constants::CHANGING_STEP_RANGE[0]) {
        servosChangingStep = changingStep;
    }
}
float Leg::GetChangingStep() {
    return servosChangingStep;
}