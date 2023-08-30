target_include_directories(LOGIC PUBLIC inc
    LOGIC PUBLIC ./../../include
    )

target_sources(LOGIC PUBLIC
    ./src/Leg.cpp
    ./src/LegPositionController.cpp
    ./src/LegServos.cpp
    ./src/gaitController.cpp
    ./src/body.cpp
    ./src/Servo.cpp
    ./src/tripodGait.cpp
    ./src/caterpillarGait.cpp
    ./src/metachromaticGait.cpp
)

    