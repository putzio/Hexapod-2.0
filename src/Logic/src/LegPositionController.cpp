#include "LegPositionController.hpp"
#include <stdio.h>

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
    LegPositionController::LegPositionController(ServosPositions servos, Side knee) {
        if (knee == Side::KNEE_FRONT) {
            calculateServoPositionsPtr = CalculateServoPositions_KneeFront;
        }
        else {
            calculateServoPositionsPtr = CalculateServoPositions_KneeBack;
        }
        p_coordinates = FindXYPosition(servos);
    }

    Result LegPositionController::CalculateYPosition(const SingleCoordinate& xPos) {
        if (!xPos.IsBetween(p_legRange.x)) {
            return RESULT_COORDINATES_OUT_OF_RANGE;
        }
        // SingleCoordinate DELTA_SENSING_Y;
        // DELTA_SENSING_Y.SetCoordinate_mm(8);
        SingleCoordinate xMapped = MapXInRange(xPos);
        p_coordinates.y = (1.0 - sin(xMapped.GetCoordinate() * 3.1415)) * //sin^2?
            (double)(p_footOnGroundY[1].GetCoordinate() - p_footOnGroundY[0].GetCoordinate())
            + p_footOnGroundY[0].GetCoordinate();// - DELTA_SENSING_Y.GetCoordinate();
        return RESULT_OK;
    }

    inline SingleCoordinate LegPositionController::MapXInRange(const SingleCoordinate& xPos) {
        return (xPos - p_legRange.x[0]) / (p_legRange.x[1] - p_legRange.x[0]);
    }

    ServosPositions LegPositionController::CalculateServoPositions_KneeFront(const float xNew, const float yNew) {
        ServosPositions servosPositions;
        //p_coordinates.x = xNew; p_coordinates.y = yNew;
        float dSquared = pow(xNew, 2) + pow(yNew, 2);
        float gamma = acos((2.0f - dSquared) / 2);
        float alpha = atan2(yNew, xNew) - (Constants::PI - gamma) / 2;

        servosPositions.upperServoAngle = Constants::PI - alpha;
        servosPositions.lowerServoAngle = gamma - (Constants::PI / 2.0);

        return servosPositions;
    }

    ServosPositions LegPositionController::CalculateServoPositions_KneeBack(const float xNew, const float yNew) {
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
            CalculateYPosition(p_coordinates.x);
        }
        else {
            p_coordinates.y = p_footOnGroundY[1];
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

    Result LegPositionController::SetNewXYPosition(SingleCoordinate xNew, SingleCoordinate yNew) {
        float maxRange = Constants::LEG_LENGTH * Constants::LEG_LENGTH;
        if (xNew.GetCoordinate() * xNew.GetCoordinate() + yNew.GetCoordinate() * yNew.GetCoordinate() > maxRange) {
            return RESULT_COORDINATES_OUT_OF_RANGE;
        }
        ReturnOnError(SetX(xNew));
        return SetY(yNew);
    }

    Result LegPositionController::SetNewXYPosition(const FootCoordinates& coordinates) {
        return SetNewXYPosition(coordinates.x, coordinates.y);
    }

    Result LegPositionController::SetLegRange(const LegRange& legRange) {
        p_legRange = legRange;
        return RESULT_OK;
    }

    void LegPositionController::SetFootHights(std::array<SingleCoordinate, 2> hights) {
        p_footOnGroundY[0] = hights[0];
        p_footOnGroundY[1] = hights[1];
    }

    Result LegPositionController::SetStandUp() {
        p_coordinates.x = 0;
        p_coordinates.y = p_legRange.y[1];
        return RESULT_OK;
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

    Result LegPositionController::SetX(SingleCoordinate xNew) {
        if (!xNew.IsBetween(p_legRange.x)) {
            return RESULT_COORDINATES_OUT_OF_RANGE;
        }
        p_coordinates.x = xNew;
        return RESULT_OK;
    }
    Result LegPositionController::SetY(SingleCoordinate yNew) {
        if (!yNew.IsBetween(p_legRange.y)) {
            return RESULT_COORDINATES_OUT_OF_RANGE;
        }
        p_coordinates.y = yNew;

        return RESULT_OK;
    }

    ServosPositions LegPositionController::CalculateServoPositions(const float xNew, const float yNew) {
        return (this->calculateServoPositionsPtr)(xNew, yNew);
    }

    ServosPositions LegPositionController::CalculateServoPositions(const FootCoordinates& coordinates) {
        return CalculateServoPositions(coordinates.x.GetCoordinate(), coordinates.y.GetCoordinate());
    }

    ServosPositions LegPositionController::CalculateServoPositions() {
        return CalculateServoPositions(p_coordinates);
    }
}