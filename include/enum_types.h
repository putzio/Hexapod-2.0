#pragma once
enum Mode:uint8_t
{
    StopMode,
    ForwardMode,
    BackMode,
    LeftMode,
    RightMode,
    ResetMode,
    Pos90Mode,
};

// enum LegState
// {
//     Stop,
//     Forward,
//     MasterLoop,
//     SlaveLoop,
//     Back,
//     Up,
//     Up1,
//     Up2,
//     Down,
//     Down1,
//     Down2,
//     Left,
//     Right,
//     ResetMaster,
//     ResetSlave,
// };
//change to body states???
enum State:uint8_t
{
    Stop,
    Forward,
    MasterLoop,
    SlaveLoop,
    Back,
    Up,
    Up1,
    Up2,
    Down,
    Down1,
    Down2,
    Left,
    Right,
    ResetMaster,
    ResetSlave,
};