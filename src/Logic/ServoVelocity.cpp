#include "Logic/ServoVelocity.hpp"

#define IS_BETWEEN(x, min, max) (x > min && x < max)

ServoVelocity::ServoVelocity()
{
    velocity = MIN_VELOCITY;
    velocityLimits[1] = MAX_VELOCITY;
    velocityLimits[0] = MIN_VELOCITY;
}

Result ServoVelocity::ChangeVelocityLimits(int vMin, int vMax){
    if(!IS_BETWEEN(vMin, MIN_VELOCITY, MAX_VELOCITY) && !IS_BETWEEN(vMax, MIN_VELOCITY, MAX_VELOCITY))
        return kVelocityOutOfRange;
    velocityLimits[0] = vMin;
    velocityLimits[1] = vMax;
    return kOkResult;
}
void ServoVelocity::CalculateVelocity(int16_t distance){//CHECK
    // if(currentPosition - msPosition < DISTANCE_DECCELERATION &&
    //     currentPosition - msPosition > - DISTANCE_DECCELERATION )
    if (IS_BETWEEN(distance, -DISTANCE_DECCELERATION, DISTANCE_DECCELERATION))
    {
        // deccelerate
        velocity -= DECCELERATION;
    }
    else
    {
        // accelerate
        velocity += ACCELERATION;
    }

    if (velocity < velocityLimits[0])
        velocity = velocityLimits[0];
    if (velocity > velocityLimits[1])
        velocity = velocityLimits[1];
}

float ServoVelocity::GetVelocity()
{
    return velocity;
}
const int16_t* ServoVelocity::GetVelocityLimits()
{
    return velocityLimits;
}