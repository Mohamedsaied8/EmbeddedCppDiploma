#pragma once
#include "i_engine.h"
#include <gmock/gmock.h>

class MockEngine : public IEngine {
public:
    MOCK_METHOD(void, Start, (), (override));
    MOCK_METHOD(void, Stop, (), (override));
};
