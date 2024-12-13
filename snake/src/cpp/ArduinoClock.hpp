#pragma once

#include "IClock.hpp"

class ArduinoClock : public IClock
{
public: 
    inline unsigned int GetTick() const;
};

#include "ArduinoClock.inl"