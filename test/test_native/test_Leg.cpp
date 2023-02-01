#include <gtest/gtest.h>

#include"Logic/Leg.hpp"
#include <memory>

TEST(Leg, test_init) {
    Leg leg = Leg(Side::KNEE_BACK);
}

TEST(Leg, test_SetNewTargetPosition) {
    Leg leg = Leg(Side::KNEE_BACK);
    FootTargetPosition coordinates;
    coordinates.x = 7;//7mm
    coordinates.footOnGround = true;
    leg.SetNewTargetPosition(coordinates);

}

// TEST(Leg, test_MoveLegToTarget_x_zero){
//     Leg leg = Leg(Side::LEFT, Side::KNEE_BACK);

//     const LegServos* const ptr_servos = leg.GetServosPtr();
//     Coordinates coordinates;
//     coordinates.x = 0;
//     coordinates.y = 70;
//     leg.MoveLegToTheXYTarget(coordinates);

//     ServosPositions expected;
//     expected.lowerServoAngle = - Constants::PI / 6.0;
//     expected.upperServoAngle = 5.0 * Constants::PI / 6.0;

//     // ASSERT_NEAR(expected.lowerServoAngle, ptr_servos->lowerServo.GetTargetAngle(), 0.001);//The negative values???
//     ASSERT_NEAR(expected.upperServoAngle, ptr_servos->upperServo.GetTargetAngle(), 0.001);
// }

// TEST(Leg, test_MoveLegToTarget){
//     Leg leg = Leg(Side::LEFT, Side::KNEE_BACK);

//     const LegServos* const ptr_servos = leg.GetServosPtr();
//     Coordinates coordinates;
//     coordinates.x = 0.5000 * 70;
//     coordinates.y = 1.8660 * 70;
//     leg.MoveLegToTheXYTarget(coordinates);

//     ServosPositions expected;
//     expected.lowerServoAngle = Constants::PI / 3.0;
//     expected.upperServoAngle = 2.0 * Constants::PI / 3.0;

//     ASSERT_NEAR(expected.lowerServoAngle, ptr_servos->lowerServo.GetTargetAngle(), 0.001);//The negative values???
//     ASSERT_NEAR(expected.upperServoAngle, ptr_servos->upperServo.GetTargetAngle(), 0.001);
// }