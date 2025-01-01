#pragma once
#include "i_engine.h"
#include <memory>

class Car
{
public:
    Car(std::unique_ptr<IEngine>&& engine);

    void Drive();
    void Stop();
private:
    std::unique_ptr<IEngine> m_engine; 
};