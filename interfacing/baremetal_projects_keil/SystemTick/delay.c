#include "delay.h"
 
// For store tick counts in us
static volatile uint32_t usTicks;
 
// SysTick_Handler function will be called every 1 ms
//8000000/8000=1000
void SysTick_Handler()
{
    if (usTicks != 0)
    {
        usTicks--;
    }
}
 
void DelayInit()
{
    // Update SystemCoreClock value
	SysTick->LOAD = 7999;

    // Configure the SysTick timer to overflow every 1 us
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

}
 
void DelayUs(uint32_t us)
{
    // Reload us value
    usTicks = us;
    // Wait until usTick reach zero
    while (usTicks);
}
 
void DelayMs(uint32_t ms)
{
    // Wait until ms reach zero
    while (ms--)
    {
        // Delay 1ms
        DelayUs(1);
    }
}