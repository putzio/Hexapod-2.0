#include "Logic/ServoVelocity.hpp"
#include "gtest/gtest.h"

TEST(ServoVelocity, test_initialises_Servo_Velocity){
    // initialise the right servo
    ServoVelocity velocity;
    ASSERT_EQ(MIN_VELOCITY, velocity.GetVelocity());
}

TEST(ServoVelocity, test_calculates_servo_velocity)
{
    ServoVelocity velocity;
    
    int16_t distance = 0;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(MIN_VELOCITY, velocity.GetVelocity());

    distance = DISTANCE_DECCELERATION + 1;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(float(MIN_VELOCITY + ACCELERATION), velocity.GetVelocity());

    distance = 0;
    velocity.CalculateVelocity(distance);
    ASSERT_EQ(MIN_VELOCITY, velocity.GetVelocity());
    
    // velocity.GetVelocity() = MAX_VELOCITY;
    // distance = DISTANCE_DECCELERATION + 2;
    // ASSERT_EQ(MAX_VELOCITY,velocity.GetVelocity());
}
TEST(ServoVelocity, test_change_velocity)
{
    ServoVelocity velocity;
    int16_t v1 = 10, v2 = 20;
    
    velocity.ChangeVelocityLimits(v1,v2);
    const int16_t* velocities = velocity.GetVelocityLimits();
    ASSERT_EQ(v1, velocities[0]);
    ASSERT_EQ(v2, velocities[1]);
}