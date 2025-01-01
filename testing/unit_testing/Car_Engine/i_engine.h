#pragma once

class IEngine
{
    public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual ~IEngine() = default;
};