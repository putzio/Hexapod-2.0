#pragma once

#define ReturnOnError(result) ({ \
    Result r = result; \
    if (r != RESULT_OK) \
        return r; \
})

#define ReturnUnexpected(result, unexpectedResult) ({ \
    Result r = result; \
    if (r == unexpectedResult) \
        return r; \
})

typedef enum Result {
    RESULT_OK,

    RESULT_SERVO_IN_TARGET_POSITION,
    RESULT_SERVO_MOVING,
    RESULT_SERVO_VELOCITY_EQ_0,
    RESULT_SERVO_VELOCITY_OUT_OF_RANGE,
    RESULT_SERVO_ANGLE_OUT_OF_RANGE,


    RESULT_COORDINATES_OUT_OF_RANGE,
    RESULT_HIGHT_OUT_OF_RANGE,

    RESULT_LEG_IN_TARGET_POSITION,
    RESULT_LEG_NEW_CONTROLLER_POSITION,
    RESULT_LEG_MOVING,

    RESULT_LEGS_NOT_IN_DEFAULT_POSITION,

    RESULT_WRONG_GAIT,
    RESULT_CHOSEN_GAIT_IS_CURRENT_GAIT,
    RESULT_DIRECTION_NOT_CHOSEN,

    RESULT_UNDEFINED_ERROR
}Result;