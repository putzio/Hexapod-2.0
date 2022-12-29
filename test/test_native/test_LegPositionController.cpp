#include "Logic/LegPositionController.hpp"
#include <gtest/gtest.h>

TEST(LegPositionController, test_initialise_controller)
{
    LegPositionController controller = LegPositionController();
    LegPositionController newController(0.01, 0.01);

    ASSERT_NEAR(0, controller.GetX(), 0.001);
    ASSERT_NEAR(1.7320, controller.GetY(), 0.001); //(sin(60.0*PI/180.0) * 20000.0)

    ASSERT_NEAR(0.01, newController.GetX(), 0.001);
    ASSERT_NEAR(0.01, newController.GetY(), 0.001);
}

TEST(LegPositionController, test_CalculateYPosition){
    LegPositionController controller = LegPositionController();
    
    controller.CalculateYPosition(controller.xRange[0]);
    ASSERT_NEAR(controller.yRange[1], controller.GetY(), 0.001);

    controller.CalculateYPosition(controller.xRange[1]);
    ASSERT_NEAR(controller.yRange[1], controller.GetY(), 0.001);

    controller.CalculateYPosition((controller.xRange[0] + controller.xRange[1])/2);
    ASSERT_NEAR(controller.yRange[0], controller.GetY(), 0.001);
}

TEST(LegPositionController, test_calculateServoPositions){
    LegPositionController controller = LegPositionController();
    float x =  0.5000; 
    float y = 1.8660;//1+sin(60*)
    ServosPositions expected;
    expected.LowerServoAngle = PI / 3.0;
    expected.UpperServoAngle = 2.0 * PI / 3.0;

    ServosPositions actual = controller.CalculateServoPositions(x,y);
    ASSERT_NEAR(expected.LowerServoAngle, actual.LowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.UpperServoAngle, actual.UpperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}

TEST(LegPositionController, test_calculateServoPositions_x_eq_zero){
    LegPositionController controller = LegPositionController();
    float x = 0; 
    float y = 1.0000;
    ServosPositions expected;
    expected.LowerServoAngle = - PI / 6.0;
    expected.UpperServoAngle = 5.0 * PI / 6.0;

    ServosPositions actual = controller.CalculateServoPositions(x,y);
    ASSERT_NEAR(expected.LowerServoAngle, actual.LowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.UpperServoAngle, actual.UpperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}

TEST(LegPositionController, test_Find_XY_Position){
    LegPositionController controller = LegPositionController();
    
    ServosPositions positions;
    positions.UpperServoAngle = 5.0 * PI / 6.0;
    positions.LowerServoAngle = - PI / 6.0;
    
    controller.FindXYPosition(positions);
    float expectedX = 0;
    float expectedY = 1.0000; 
    ASSERT_NEAR(expectedX, controller.GetX(), 0.001);
    ASSERT_NEAR(expectedY, controller.GetY(), 0.001);
}