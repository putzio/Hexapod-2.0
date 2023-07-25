#pragma once

#include <stdint.h>
#include <cmath>
#include "constants.hpp"
#include "FootCoordinates.hpp"
#include "Results.h"
#include "ServoPositions.hpp"
#include "LegRange.hpp"
#include <functional>

namespace logic::leg {
  typedef enum Side :uint8_t {
    UNDEFINED,
    KNEE_BACK,
    KNEE_FRONT
  }Side;

  // back and front
  class LegPositionController {
  protected:
    FootCoordinates p_coordinates;
    LegRange p_legRange;
    SingleCoordinate p_footOnGroundY[2] = { 1.4, 1.7320f };//sin(60.0 * Constants::PI / 180.0) * 20000.0 = 1.7320f

  private:
    typedef std::function < ServosPositions(float xNew, float yNew)>CalculateServoPositionsFunctionPointer;
    SingleCoordinate MapXInRange(const SingleCoordinate& xPos);
    CalculateServoPositionsFunctionPointer calculateServoPositionsPtr;
    static ServosPositions CalculateServoPositions_KneeBack(float xNew, float yNew);
    static ServosPositions CalculateServoPositions_KneeFront(float xNew, float yNew);

  public:
    LegPositionController(Side knee = Side::KNEE_BACK) : LegPositionController(0, Constants::Y_ABSOLUTE_RANGE[1], knee) {};
    LegPositionController(FootCoordinates coordinates, Side knee = Side::KNEE_BACK) :LegPositionController(coordinates.x, coordinates.y, knee) {};
    LegPositionController(SingleCoordinate x, SingleCoordinate y, Side knee = Side::KNEE_BACK);
    LegPositionController(ServosPositions servos, Side knee = Side::KNEE_BACK);

    /**
     *   \brief Calculate the y position when the leg is up
     *   When the leg is up, the foot's path is a sin function
     *
     *   \param xPos the x position of the end of the leg
     *   The point (0,0) is in the Upper servomotor joint
     *   \return struct ServoPositions with values of angles for both servomotors
     *
     **/
    Result CalculateYPosition(const SingleCoordinate& xPos);

    /**
     * @brief Calculates coordinates to set servos in,
     *  for the x closer to target coordinates by the Constants::DELTA_X
     *
     * @param xTarget the target x position
     * @param LegUp bool defining if the coordinates should be calulated assuming
     * the leg will be up or it will stay on the ground
     *
     * @return float
     */
    FootCoordinates FindNextCoordinates(const SingleCoordinate& xTarget, const bool& footOnGround);
    FootCoordinates FindNextCoordinates(const FootTargetPosition& target);

    /**
   *   \brief Find the xy position based on the servomotors
   *   angles and write it to the p_coordinates
   *
   *   \param positions resference to the servomotors positions
   *
   **/
    FootCoordinates FindXYPosition(const ServosPositions& positions);

    /**
     *   \brief Calculate the servomotors positions
     *
     *   \param newX, newY the position of the end of the leg.
     *   The point (0,0) is in the Upper servomotor joint
     *   \return struct ServoPositions with values of angles for both servomotors
     *
     **/
    ServosPositions CalculateServoPositions(float xNew, float yNew);
    ServosPositions CalculateServoPositions(const FootCoordinates& coordinates);
    ServosPositions CalculateServoPositions();

    SingleCoordinate GetX();
    SingleCoordinate GetY();
    const FootCoordinates& GetCoordinates()const;
    const LegRange& GetLegRange()const;
    const SingleCoordinate& GetFootOnGroundY()const { return p_footOnGroundY[1]; };
    const SingleCoordinate& GetFootUpY()const { return p_footOnGroundY[0]; };

    /**
     *   \brief Set current xy position
     *
     *   \param newX, newY the position of the end of the leg.
     *   The point (0,0) is in the Upper servomotor joint
     *
     **/
    Result SetNewXYPosition(SingleCoordinate xNew, SingleCoordinate yNew);
    Result SetNewXYPosition(const FootCoordinates& coordinates);
    Result SetLegRange(const LegRange& legRange);

  private:
    Result SetX(SingleCoordinate xNew);
    Result SetY(SingleCoordinate yNew);
  };
}