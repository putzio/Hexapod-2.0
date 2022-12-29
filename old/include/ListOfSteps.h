#pragma once
#include "enum_types.h"

const State forwardStates[] = {
    Stop,
    Forward,
    MasterLoop,
    Down1,
    SlaveLoop,
    Down2,
    SlaveLoop,
    Back,
    MasterLoop,
    Up1,
    SlaveLoop,
    Up2,
    SlaveLoop};
const State backStates[] = {
    Stop,
    Forward,
    MasterLoop,
    Up1,
    SlaveLoop,
    Up2,
    SlaveLoop,
    Back,
    MasterLoop,
    Down1,
    SlaveLoop,
    Down2,
    SlaveLoop};
const State leftStates[] = {
    Stop,
    Right,
    MasterLoop,
    Up1,
    SlaveLoop,
    Up2,
    SlaveLoop,
    Left,
    MasterLoop,
    Down1,
    SlaveLoop,
    Down2,
    SlaveLoop};
const State rightStates[] = {
    Stop,
    Right, // L1 Back
    MasterLoop,
    Down1,
    SlaveLoop,
    Down2,
    SlaveLoop,
    Left, // L1 Forward
    MasterLoop,
    Up1,
    SlaveLoop,
    Up2,
    SlaveLoop};
const State resetStates[] = {
    Stop,
    ResetMaster,
    MasterLoop,
    ResetSlave,
    SlaveLoop,
    Stop};
const State pos90States[] = {
    Stop,
    SlaveLoop,
    Stop};