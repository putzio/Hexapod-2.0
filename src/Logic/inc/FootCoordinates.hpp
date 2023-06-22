#pragma once

#include <cmath>
#include "constants.hpp"

namespace logic::leg {
  typedef struct SingleCoordinate {
  private:
    float value;
  public:
    SingleCoordinate(float v = 0) { value = v; }
    void SetCoordinate_mm(float v) { value = v / Constants::LEG_LENGTH; }
    void SetCoordinate(float v) { value = v; }
    float GetCoordinate_mm() const { return value * Constants::LEG_LENGTH; }
    float GetCoordinate() const { return value; }

    SingleCoordinate operator + (const float& other) { return value + other; }
    SingleCoordinate operator - (const float& other) { return value - other; }
    SingleCoordinate operator * (const float& other) { return value * other; }
    SingleCoordinate operator / (const float& other) { return value / other; }

    SingleCoordinate operator + (const SingleCoordinate& other) { return value + other.GetCoordinate(); }
    SingleCoordinate operator - (const SingleCoordinate& other) { return value - other.GetCoordinate(); }
    SingleCoordinate operator * (const SingleCoordinate& other) { return value * other.GetCoordinate(); }
    SingleCoordinate operator / (const SingleCoordinate& other) { return value / other.GetCoordinate(); }

    SingleCoordinate operator+=(const float& other) { *this = *this + other;    return *this; }
    SingleCoordinate operator-=(const float& other) { *this = *this - other;    return *this; }
    SingleCoordinate operator*=(const float& other) { *this = *this * other;    return *this; }
    SingleCoordinate operator/=(const float& other) { *this = *this / other;    return *this; }

    SingleCoordinate operator = (const float& other) { value = other;    return *this; }
    SingleCoordinate operator = (const SingleCoordinate& other) { value = other.GetCoordinate();    return *this; }
    bool operator==(const SingleCoordinate& other)const { return std::abs(value - other.GetCoordinate()) < 0.001; }
    bool operator!=(const SingleCoordinate& other)const { return !(*this == other); }
    bool operator>(const SingleCoordinate& other)const { return value > other.GetCoordinate(); }
    bool operator<(const SingleCoordinate& other)const { return value < other.GetCoordinate(); }

    bool IsBetween(const float range[2]) const { return (value >= range[0] && value <= range[1]); }
  }SingleCoordinate;

  typedef struct FootTargetPosition {
    SingleCoordinate x;
    bool footOnGround;
    FootTargetPosition(SingleCoordinate x = 0, bool footOnGround = true) { this->x = x;this->footOnGround = footOnGround; };
    void SetCoordinates_mm(const float& x, bool footOnGround) {
      this->x.SetCoordinate_mm(x);
      this->footOnGround = footOnGround;
    }
    void SetCoordinates(const float& x, bool footOnGround) {
      this->x.SetCoordinate(x);
      this->footOnGround = footOnGround;
    }

    bool operator == (const FootTargetPosition& other)const {
      return std::abs(this->x.GetCoordinate() - other.x.GetCoordinate()) < 0.0001 && this->footOnGround == other.footOnGround;
    }
    bool operator != (const FootTargetPosition& other)const {
      return !(*this == other);
    }
  }FootTargetPosition;

  typedef struct FootCoordinates {
    SingleCoordinate x, y;
    void SetCoordinates_mm(const float& x, const float& y) {
      this->x.SetCoordinate_mm(x);
      this->y.SetCoordinate_mm(y);
    }
    float GetX_mm()const {
      return this->x.GetCoordinate_mm();
    }
    float GetY_mm()const {
      return this->y.GetCoordinate_mm();
    }

    bool operator==(const FootCoordinates& other)const {
      return std::abs(this->x.GetCoordinate() - other.x.GetCoordinate()) < 0.0001 && std::abs(this->y.GetCoordinate() - other.y.GetCoordinate()) < 0.0001;
    }
    bool operator!=(const FootCoordinates& other)const {
      return !(*this == other);
    }
    FootCoordinates operator/(const float& other) {
      x /= other;
      y /= other;
      return *this;
    }
    FootCoordinates operator/=(const float& other) {
      *this = *this / other;
      return *this;
    }

    bool IsBetween(const float xRange[2], const float yRange[2])const {
      if (!x.IsBetween(xRange)) {
        return false;
      }
      return y.IsBetween(yRange);
    }

  }FootCoordinates;
}