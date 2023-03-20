#include "../inc/Leg.hpp"

// Leg::Leg(Side knee) {
//     switch (knee) {
//     case KNEE_BACK:
//         p_controller.reset(new LegPositionController_KneeBack());
//         break;
//     case KNEE_FRONT:
//         p_controller.reset(new LegPositionController_KneeFront());
//         break;
//     default:

//         break;
//     }
// }
// Leg::Leg(LegServos& servos, LegPositionControllerInterface& controller) {
//     *p_controller = controller;
//     p_servos = servos;
// }

Result Leg::LegPeriodicProcess() {
    if (p_servos.GoToTargetAngle() != RESULT_SERVO_IN_TARGET_POSITION) {
        return RESULT_LEG_MOVING;
    }
    if (p_controller.GetCoordinates().x == p_finalTargetPostion.x) {
        return RESULT_LEG_IN_TARGET_POSITION;
    }
    p_controller.FindNextCoordinates(p_finalTargetPostion.x, p_finalTargetPostion.footOnGround);
    return RESULT_LEG_NEW_CONTROLLER_POSITION;
}

void Leg::MoveLegToTheXYTarget(const ServosPositions* positions) {
    if (positions != nullptr) {
        p_servos.SetTargetAngle(positions->upperServoAngle, positions->lowerServoAngle);
        return;
    }
    ServosPositions p = p_controller.CalculateServoPositions();
    positions = &p;
    p_servos.SetTargetAngle(positions->upperServoAngle, positions->lowerServoAngle);
}


bool Leg::LegInFinalTargetPosition(const FootCoordinates& coordinates) {//for y?
    return (std::abs(p_finalTargetPostion.x - coordinates.x) < Constants::DELTA_X);
}

Result Leg::SetNewTargetPosition(const FootTargetPosition& coordinates) {
    FootTargetPosition newCoordinates = FootTargetPosition(coordinates.x, coordinates.footOnGround);
    newCoordinates.x /= Constants::LEG_LENGTH;
    if (newCoordinates.x < p_controller.GetLegRange().x[0] || newCoordinates.x > p_controller.GetLegRange().x[1]) {
        return RESULT_COORDINATES_OUT_OF_RANGE;
    }
    p_finalTargetPostion = newCoordinates;
    p_controller.FindNextCoordinates(p_finalTargetPostion.x, p_finalTargetPostion.footOnGround);
    return RESULT_OK;
}
Result Leg::SetNewTargetPosition(const FootCoordinates& coordinates) {
    p_controller.SetNewXYPosition(coordinates);
}


const FootTargetPosition& Leg::GetFootCoordinates() const {
    return p_finalTargetPostion;
}