#pragma once

#include "buzzer.h"

namespace Vehicle
{
    class Alarm
    {
        public:
            Alarm(hal::Buzzer *c_buzzer);
            void setAlarm(bool state);
            uint32_t getAlarm();
        private:
        hal::Buzzer *buzzer; //pimpl idiom
        uint32_t m_state;
    };
}
