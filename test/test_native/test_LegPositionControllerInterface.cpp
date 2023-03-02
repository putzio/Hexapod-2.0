// #include "../../Logic/inc/Leg.hpp"
// #include "../../Logic/inc/LegPositionController_KneeFront.hpp"
// #include <gtest/gtest.h>
// #include "memory"

// TEST(LegPositionControllerInterface, test_initialise_controller) {
//     std::unique_ptr<LegPositionControllerInterface> controller = std::make_unique<LegPositionController_KneeFront>();
//     std::unique_ptr<LegPositionControllerInterface> newController = std::make_unique<LegPositionController_KneeFront>(0.01, 0.01);

//     ASSERT_NEAR(0, controller->GetX(), 0.001);
//     ASSERT_NEAR(1.7320, controller->GetY(), 0.001); //(sin(60.0*Constants::PI/180.0) * 20000.0)

//     ASSERT_NEAR(0.01, newController->GetX(), 0.001);
//     ASSERT_NEAR(0.01, newController->GetY(), 0.001);
// }

// TEST(LegPositionControllerInterface, test_CalculateYPosition) {
//     std::unique_ptr<LegPositionControllerInterface> controller = std::make_unique<LegPositionController_KneeFront>();

//     controller->CalculateYPosition(controller->GetLegRange().x[0]);
//     ASSERT_NEAR(controller->GetLegRange().y[1], controller->GetY(), 0.001);

//     controller->CalculateYPosition(controller->GetLegRange().x[1]);
//     ASSERT_NEAR(controller->GetLegRange().y[1], controller->GetY(), 0.001);

//     controller->CalculateYPosition((controller->GetLegRange().x[0] + controller->GetLegRange().x[1]) / 2);
//     ASSERT_NEAR(controller->GetLegRange().y[0], controller->GetY(), 0.001);
// }

// TEST(LegPositionControllerInterface, test_Find_XY_Position) {
//     std::unique_ptr<LegPositionControllerInterface> controller = std::make_unique<LegPositionController_KneeFront>();

//     ServosPositions positions;
//     positions.upperServoAngle = 5.0 * Constants::PI / 6.0;
//     positions.lowerServoAngle = -Constants::PI / 6.0;

//     controller->FindXYPosition(positions);
//     float expectedX = 0;
//     float expectedY = 1.0000;
//     ASSERT_NEAR(expectedX, controller->GetX(), 0.001);
//     ASSERT_NEAR(expectedY, controller->GetY(), 0.001);
// }

// TEST(LegPositionControllerInterface, test_CalculateNextCoordinates) {
//     std::unique_ptr<LegPositionControllerInterface> controller = std::make_unique<LegPositionController_KneeFront>();
//     float targetX = 6.5;
//     bool footOnGround = false;

//     FootCoordinates actual = controller->FindNextCoordinates(targetX, footOnGround);
//     ASSERT_NEAR(5.0, actual.x, 0.001);
//     ASSERT_NEAR(controller->CalculateYPosition(5.0), actual.y, 0.001);

//     actual = controller->FindNextCoordinates(targetX, footOnGround);
//     ASSERT_NEAR(6.5, actual.x, 0.001);
//     ASSERT_NEAR(controller->CalculateYPosition(6.5), actual.y, 0.001);

//     targetX = 5.0;
//     footOnGround = true;
//     actual = controller->FindNextCoordinates(targetX, footOnGround);
//     ASSERT_NEAR(5.0, actual.x, 0.001);
//     ASSERT_NEAR(controller->GetLegRange().y[1], actual.y, 0.001);
// }