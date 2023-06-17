#include "../inc/LegPositionController.hpp"

namespace logic::leg {
    LegPositionController::LegPositionController(SingleCoordinate x, SingleCoordinate y, Side knee) {
        if (knee == Side::KNEE_FRONT) {
            calculateServoPositionsPtr = CalculateServoPositions_KneeFront;
        }
        else {
            calculateServoPositionsPtr = CalculateServoPositions_KneeBack;
        }
        p_coordinates.x = x;
        p_coordinates.y = y;
    }

    SingleCoordinate LegPositionController::CalculateYPosition(const SingleCoordinate& xPos) {
        if (!xPos.IsBetween(p_legRange.x)) {
            return -1;
        }
        float xMapped = MapXInRange(xPos.GetCoordinate());
        p_coordinates.y = (1.0 - sin(xMapped * 3.1415)) * (double)(p_legRange.y[1] - p_legRange.y[0]) + p_legRange.y[0];
        return p_coordinates.y;
    }

    float LegPositionController::MapXInRange(const float& xPos) {
        return (xPos - p_legRange.x[0]) / (p_legRange.x[1] - p_legRange.x[0]);
    }

    ServosPositions LegPositionController::CalculateServoPositions_KneeFront(float xNew, float yNew) {
        ServosPositions servosPositions;
        //p_coordinates.x = xNew; p_coordinates.y = yNew;
        float dSquared = pow(xNew, 2) + pow(yNew, 2);
        float gamma = acos((2 - dSquared) / 2);
        float alpha = atan2(yNew, xNew) - (Constants::PI - gamma) / 2;

        servosPositions.upperServoAngle = Constants::PI - alpha;
        servosPositions.lowerServoAngle = gamma - (Constants::PI / 2.0);

        return servosPositions;
    }

    ServosPositions LegPositionController::CalculateServoPositions_KneeBack(float xNew, float yNew) {
        ServosPositions servosPositions;
        float dSquared = pow(xNew, 2) + pow(yNew, 2);
        float gamma = acos((2.0f - dSquared) / 2.0f);
        float alpha = -atan2(yNew, xNew) + (Constants::PI + gamma) / 2;

        servosPositions.upperServoAngle = alpha;
        servosPositions.lowerServoAngle = Constants::PI * 3.0f / 2.0f - gamma;

        return servosPositions;
    }

    FootCoordinates LegPositionController::FindNextCoordinates(const SingleCoordinate& xTarget, const bool& footOnGround) {
        if (std::abs((p_coordinates.x - xTarget).GetCoordinate()) < Constants::DELTA_X) {
            p_coordinates.x = xTarget;
        }
        else if (xTarget < p_coordinates.x) {
            p_coordinates.x -= Constants::DELTA_X;
        }
        else {
            p_coordinates.x += Constants::DELTA_X;
        }

        if (!footOnGround) {
            p_coordinates.y = CalculateYPosition(p_coordinates.x);
        }
        else {
            p_coordinates.y = p_legRange.y[1];
        }
        return p_coordinates;
    }


    FootCoordinates LegPositionController::FindNextCoordinates(const FootTargetPosition& target) {
        return FindNextCoordinates(target.x, target.footOnGround);
    }

    SingleCoordinate LegPositionController::GetX() {
        return p_coordinates.x;
    }
    SingleCoordinate LegPositionController::GetY() {
        return p_coordinates.y;
    }

    const FootCoordinates& LegPositionController::GetCoordinates() const {
        return p_coordinates;
    }
    const LegRange& LegPositionController::GetLegRange() const {
        return p_legRange;
    }

    void LegPositionController::SetNewXYPosition(SingleCoordinate xNew, SingleCoordinate yNew) {
        SetX(xNew);
        SetY(yNew);
    }

    void LegPositionController::SetNewXYPosition(const FootCoordinates& coordinates) {
        SetNewXYPosition(coordinates.x, coordinates.y);
    }

    FootCoordinates LegPositionController::FindXYPosition(const ServosPositions& positions) {
        FootCoordinates coordinates;

        coordinates.x = (sin(positions.upperServoAngle - Constants::PI / 2) - sin(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));
        coordinates.y = (cos(positions.upperServoAngle - Constants::PI / 2) + cos(Constants::PI - positions.upperServoAngle - positions.lowerServoAngle));
        // coordinates.x = (sin(positions.upperServoAngle) + sin(3.0 * Constants::PI / 4 - positions.upperServoAngle - positions.lowerServoAngle));
        // coordinates.y = (cos(positions.upperServoAngle) + cos(3.0 * Constants::PI / 4 - positions.upperServoAngle - positions.lowerServoAngle));
        SetNewXYPosition(coordinates);
        return coordinates;
    }

    void LegPositionController::SetX(SingleCoordinate xNew) {
        if (!xNew.IsBetween(p_legRange.x)) {
            return;
        }
        p_coordinates.x = xNew;
    }
    void LegPositionController::SetY(SingleCoordinate yNew) {
        if (!yNew.IsBetween(p_legRange.y)) {
            return;
        }
        p_coordinates.y = yNew;
    }

    ServosPositions LegPositionController::CalculateServoPositions(float xNew, float yNew) {
        return (this->calculateServoPositionsPtr)(xNew, yNew);
    }

    ServosPositions LegPositionController::CalculateServoPositions(const FootCoordinates& coordinates) {
        return CalculateServoPositions(coordinates.x.GetCoordinate(), coordinates.y.GetCoordinate());
    }

    ServosPositions LegPositionController::CalculateServoPositions() {
        return CalculateServoPositions(p_coordinates);
    }
}