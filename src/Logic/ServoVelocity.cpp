#include "Logic/ServoVelocity.hpp"

#define IS_BETWEEN(x, min, max) (x > min && x < max)

ServoVelocity::ServoVelocity()
{
    velocity = MIN_VELOCITY;
    maxVelocity = MAX_VELOCITY;
    minVelocity = MIN_VELOCITY;
}

void ServoVelocity::ChangeVelocityLimits(int vMin, int vMax){
    if(IS_BETWEEN(vMin, 1, 20))
        minVelocity = vMin;
    if(IS_BETWEEN(vMax, 1, 20))
        maxVelocity = vMax;
}
void ServoVelocity::CalculateVelocity(int16_t distance){
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

    if (velocity < minVelocity)
        velocity = minVelocity;
    if (velocity > maxVelocity)
        velocity = maxVelocity;
}

float ServoVelocity::GetVelocity()
{
    return velocity;
}

void ServoVelocity::VelocityLimitGetter(int *velocities)
{
    velocities[0] = minVelocity;
    velocities[1] = maxVelocity;
}