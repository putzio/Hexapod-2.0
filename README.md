# Hexapod

## Class diagram of the project

### Robot Logic:

```mermaid
classDiagram
    %%Logic classes relations:
    LegServos *-- Servo:2
    FootCoordinates o-- SingleCoordinate:2
    FootTargetPosition o-- SingleCoordinate:1

    LegPositionController *-- FootCoordinates
    LegPositionController *-- LegRange

    Leg <|-- LegServos
    Leg *-- LegPositionController
    Leg o-- FootTargetPosition

    GaitInterface <|-- TripodGait
    GaitInterface <|-- CatepillarGait
    GaitInterface <|-- MetachronousGait
    GaitInterface o-- FootTargetPosition: 6

    GaitController *-- Leg:6
    GaitController *-- GaitInterface

    %%Logic classes:
    class Servo{
        - p_currentAngle : float
        - p_targetAngle : float
        - p_angleChangingStep : float

        + GoToTargetAngle()
        + GetCurrentAngle()
        + SetTargetAngle()
    }

    class LegServos{
        + GetServoPositions()
        + SetServosTargetPostions()
        + ServosPeriodicProcess()
    }

    class LegPositionController{
        + CalculateYPosition()
        + FindXYPosition()
        + FindNextFootCoordinates()
        + CalculateServoPositions()
        - CalculateServoPositions_KneeBack()
        - CalculateServoPositions_KneeFront()
        - CalculateServoPositionsPointer
    }
    class SingleCoordinate{
        - value: float
        + GetCoordinate()
        + GetCoordinate_mm()
        + SetCoordinate()
        + SetCoordinate_mm()
        + IsBetween()
    }
    class FootCoordinates{
    }
    class LegRange{
        + x: float[2]
        + y: float[2]

        + ChangeLegHight()
    }

    class FootTargetPosition{
        + footOnGround: bool
    }

    class Leg{

        + PeriodicProcess()
        + SetNewTargetPosition()
        + MoveJServos()
    }

    class GaitInterface{
        + GoToTheDefaultPosition()
        + virtual GoForeward()
        + virtual GoBackward()
        + virtual TurnRight()
        + virtual TurnLeft()
    }
    class TripodGait{
        + override GoForeward()
        + override GoBackward()
        + override TurnRight()
        + override TurnLeft()
    }
    class CatepillarGait{
        + override GoForeward()
        + override GoBackward()
        + override TurnRight()
        + override TurnLeft()
    }
    class MetachronousGait{
        + override GoForeward()
        + override GoBackward()
        + override TurnRight()
        + override TurnLeft()
    }

    class GaitController{
        + const enum Gait currentGait

        + PeriodicProcess()
        + ChangeGait()
    }

```

### Drivers

```mermaid
    classDiagram
    %%Driver classes relations:

    ServoDriverInterface o-- PwmDriver
    ServoDriverInterface <|-- LeftServoDriver
    ServoDriverInterface <|-- RightServoDriver

    CurrentSensorDriver --|> SpiDriver
    AccelerometerDriver --|> I2CDriver


    RobotDriver o-- ServoDriverInterface: 12
    RobotDriver o-- CurrentSensorDriver: 3
    RobotDriver o-- AccelerometerDriver
    RobotDriver o-- UartDriver
    RobotDriver *-- GaitController
    RobotDriver --|> DataPacket

    class PwmDriver{
        * pin: uint16_t
        * sliceNumber: uint16_t

        + InitPwm()
        + Enable()
        + Disable()
        + SetPwm()
    }

    class ServoDriverInterface{
        * calibrationValue: uint16_t

        * override InitPwm()
        + virtual SetServoAngle()
    }
    class LeftServoDriver{
        + override SetServoAngle()
    }
    class RightServoDriver{
        + override SetServoAngle()
    }

    class CurrentSensorDriver{
        -currentValues: uint16_t [8]

        + GetCurrentValuesPtr()
    }

    class GaitController{
        * ServoCurrentAnglePtrs: const float* [12]
        + PeriodicProcess()
        + ChangeGait()
    }

    class RobotDriver{
        + PeriodicProcess()
        - UpdateServoDrivers()
        -
    }

    class DataPacket{
        + ReadReceivedData()
        + CreatePacketToTransmit()
    }
```
