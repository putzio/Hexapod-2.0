target_sources(LOGIC PUBLIC
    ./src/Leg.cpp
    ./src/LegPositioncontroller_KneeBack.cpp
    ./src/LegPositioncontroller_KneeFront.cpp
    ./src/LegPositioncontrollerInterface.cpp
    ./src/LegServos.cpp
    ./src/MoveController.cpp
    ./src/body.cpp
    ./src/Servo.cpp
)
target_include_directories(LOGIC PUBLIC inc
    LOGIC PUBLIC ../../include)