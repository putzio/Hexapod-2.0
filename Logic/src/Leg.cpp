#include "../inc/Leg.hpp"

Leg::Leg(Side knee) {
    switch (knee) {
    case KNEE_BACK:
        p_controller = std::make_unique<LegPositionController_KneeBack>();
        break;
    case KNEE_FRONT:
        p_controller = std::make_unique<LegPositionController_KneeFront>();
        break;
    default:

        break;
    }
}

Leg::Leg(LegServos& servos, LegPositionControllerInterface& controller) {
    *p_controller = controller;
    p_servos = servos;
}

void Leg::MoveLegToTheXYTarget() {
    ServosPositions positions = p_controller->CalculateServoPositions();
    p_servos.SetTargetAngle(positions.upperServoAngle, positions.lowerServoAngle);
}


Result Leg::LegPeriodicProcess() {
    if (p_servos.GoToTargetAngle() != RESULT_SERVO_IN_TARGET_POSITION) {
        return RESULT_LEG_MOVING;
    }
    if (p_controller->GetCoordinates().x == p_finalTargetPostion.x) {
        return RESULT_LEG_IN_TARGET_POSITION;
    }
    p_controller->FindNextCoordinates(p_finalTargetPostion.x, p_finalTargetPostion.footOnGround);
    return RESULT_LEG_NEW_CONTROLLER_POSITION;
}

Result Leg::SetNewTargetPosition(const FootTargetPosition& coordinates) {
    FootTargetPosition newCoordinates = coordinates;
    newCoordinates.x /= Constants::LEG_LENGTH;
    if (newCoordinates.x < p_controller->GetLegRange().x[0] || newCoordinates.x > p_controller->GetLegRange().x[1]) {
        return RESULT_COORDINATES_OUT_OF_RANGE;
    }
    p_finalTargetPostion = newCoordinates;
    return RESULT_OK;
}

bool Leg::LegInFinalTargetPosition(const FootCoordinates& coordinates) {//for y?
    return (std::abs(p_finalTargetPostion.x - coordinates.x) < Constants::DELTA_X);
}

const FootTargetPosition& Leg::GetFootCoordinates() const {
    return p_finalTargetPostion;
}