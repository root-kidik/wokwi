#pragma once

class IClock
{
public:
    virtual ~IClock() = default;
    virtual inline unsigned int GetTick() const = 0;
};