#include "alarm.h"

Vehicle::Alarm::Alarm(hal::Buzzer *c_buzzer) : buzzer(c_buzzer)
{
    // intial state of the alarm is false
    buzzer->Buzzer_Init();
}
uint32_t Vehicle::Alarm::getAlarm()
{
    return m_state;
}
void Vehicle::Alarm::setAlarm(bool state)
{
    if(state)
    {
        buzzer->Buzzer_On();
         
    }
    else
    {
        buzzer->Buzzer_Off();
    }
    this->m_state = state;
}