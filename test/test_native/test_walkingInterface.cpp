#include <gtest/gtest.h>
#include "Logic/WalkingModes/walkingInterface.hpp"

TEST(WalkingInterface, test_mode){
    WalkingInterface interface;
    
    ASSERT_EQ(WalkingInterface::NONE, interface.GetWalkingMode());
}

TEST(WalkingInterface, test_GoForward){
    WalkingInterface interface;
    
    ASSERT_EQ(Result::RESULT_WRONG_WALKING_INTERFACE_MODE, interface.GoForeward());
}