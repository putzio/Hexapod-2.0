# Hexapod 


## Class diagram of the project 
### Robot Logic:
```mermaid
classDiagram
    %%Logic classes relations:    
    LegServos *-- Servo:2 
    
    LegPositionControllerInterface <|-- LegPositionController_KneeUp
    LegPositionControllerInterface <|-- LegPositionController_KneeDown
    LegPositionControllerInterface *-- FootCoordinates
    LegPositionControllerInterface *-- LegRange
    
    Leg <|-- LegServos
    Leg *-- LegPositionControllerInterface
    Leg o-- FootTargetPosition
    
    GaitInterface <|-- TripodGait
    GaitInterface <|-- CatepillarGait
    GaitInterface <|-- MetachronousGait
    GaitInterface o-- FootTargetPosition: 6

    RobotLogic *-- Leg:6
    RobotLogic *-- GaitInterface

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

    class LegPositionControllerInterface{
        + CalculateYPosition()
        + FindNextFootCoordinates()
        + virtual CalculateServoPositions()
    }
    class LegPositionController_KneeDown{
        + override CalculateServoPositions()
    }
    class LegPositionController_KneeUp{
        + override CalculateServoPositions()
    }

    class FootCoordinates{
        + x: float
        + y:float
    }
    class LegRange{
        + x: float[2]
        + y: float[2]

        + ChangeLegHight()
    }

    class FootTargetPosition{
        + x: float
        + footOnGround: bool
    }

    class Leg{

        + PeriodicProcess()
        + SetNewTargetPosition()
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

    class RobotLogic{
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
    RobotDriver *-- RobotLogic
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

    class RobotLogic{
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
