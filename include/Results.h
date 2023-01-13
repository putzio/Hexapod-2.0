#pragma once

typedef enum Result{
    RESULT_OK,
    
    RESULT_SERVO_IN_TARGET_POSITION,
    RESULT_SERVO_MOVING,

    RESULT_LEG_IN_TARGET_POSITION,
    RESULT_LEG_NEW_CONTROLLER_POSITION,
    RESULT_LEG_MOVING,

    RESULT_LEGS_NOT_IN_DEFAULT_POSITION,
    
    RESULT_WRONG_WALKING_INTERFACE_MODE
}Result;