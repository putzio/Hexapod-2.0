#include "Logic/LegPositionController.hpp"
#include <gtest/gtest.h>

TEST(LegPositionController, test_initialise_controller)
{
    LegPositionController controller = LegPositionController();
    LegPositionController newController(100,100);

    ASSERT_EQ(0, controller.GetX());
    ASSERT_EQ(17320, controller.GetY()); //(sin(60.0*PI/180.0) * 20000.0)

    ASSERT_EQ(100, newController.GetX());
    ASSERT_EQ(100, newController.GetY());
}

TEST(LegPositionController, test_CalculateYPosition){
    LegPositionController controller = LegPositionController();
    
    controller.CalculateYPosition(controller.xRange[0]);
    ASSERT_EQ(controller.yRange[1], controller.GetY());

    controller.CalculateYPosition(controller.xRange[1]);
    ASSERT_EQ(controller.yRange[1], controller.GetY());

    controller.CalculateYPosition((controller.xRange[0] + controller.xRange[1])/2 + 0.5);
    ASSERT_EQ(controller.yRange[0], controller.GetY());
}

TEST(LegPositionController, test_calculateServoPositions){
    LegPositionController controller = LegPositionController();
    int16_t x = 5000; 
    uint16_t y = 18660;//1+sin(60*)
    ServosPositions expected;
    expected.LowerServoAngle = PI / 3.0;
    expected.UpperServoAngle = 2.0 * PI / 3.0;
    

    /*
    d = 3,73195
    gamma = acos((2-3,73195)/2) =  149,99*
    alpha = 74,999 - (360 - gamma) / 2 = 75 - 180 - 75
    */

    ServosPositions actual = controller.CalculateServoPositions(x,y);
    ASSERT_NEAR(expected.LowerServoAngle, actual.LowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.UpperServoAngle, actual.UpperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}

TEST(LegPositionController, test_calculateServoPositions_x_eq_zero){
    LegPositionController controller = LegPositionController();
    int16_t x = 0; 
    uint16_t y = 10000;
    ServosPositions expected;
    expected.LowerServoAngle = - PI / 6.0;
    expected.UpperServoAngle = 5.0 * PI / 6.0;

    ServosPositions actual = controller.CalculateServoPositions(x,y);
    ASSERT_NEAR(expected.LowerServoAngle, actual.LowerServoAngle, 0.01);//error-> 0.5deg
    ASSERT_NEAR(expected.UpperServoAngle, actual.UpperServoAngle, 0.01);
    ASSERT_EQ(1, expected == actual);
}