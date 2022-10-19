#pragma once
enum Mode
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
enum State
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