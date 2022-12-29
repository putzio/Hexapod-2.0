#include <gtest/gtest.h>

#include<Logic/Leg.hpp>

TEST(Leg, test_leg_init)
{
    Leg leg;
}

TEST(Leg, test_ChangeVelocityLimits)
{
    Leg l;
    int expected[] = {2,4}, actual[2];

    l.ChangeLegVelocityLimits(expected[0], expected[1]);

    const int16_t *limits = l.GetVelocityLimits();
    ASSERT_EQ(expected[0], limits[0]);
    ASSERT_EQ(expected[1], limits[1]);
}

TEST(Leg, test_InitLeg)
{
    Leg leg;
    leg.InitLeg();

    // ASSERT_EQ(,leg.master.GetMsPosition())
}

// TEST(Leg, test_PeriodicProcess)
// {
//     Leg leg;
    
//     leg.LegPeriodicProcess(Leg::kBack);

    
// }