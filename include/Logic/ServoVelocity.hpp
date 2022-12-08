#pragma once

#include <stdint.h>
#include "Result.hpp"

#define ACCELLERATION_PER_S 50.0
#define ACCELERATION 0.2 // ACCELERATION_PER_S*CYCLE_TIME *(SERVO_MAX_MS - SERVO_MIN_MS)/180
#define DECCELERATION 1
#define MAX_VELOCITY 20 // 20/(2400-550)/0.02 = 97*/s //in datasheet max speed -> 60*/0.1s = 600*/s
#define MIN_VELOCITY 1
#define DISTANCE_DECCELERATION 200

class ServoVelocity
{
private:
    float velocity;  // is changed and calculated in CalculateVelocity() method
    int16_t velocityLimits[2];
public:
    ServoVelocity();
    Result ChangeVelocityLimits(int vMin, int vMax);
    void CalculateVelocity(int16_t distance);
    
    float GetVelocity();
    const int16_t* GetVelocityLimits();
};



