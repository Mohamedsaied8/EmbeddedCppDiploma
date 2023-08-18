/*
 * delay.c
 *
 *      Author: MohamedSaid
 */

#include "stm32f1xx_hal.h"

#include "delay.h"
#define OSC     8000000  //8 Mhz
#define MILLIS_IN_SEC	1000

// For store tick counts in ms
static volatile uint32_t  Ticks;


void SysTick_Handler()
{
   if(Ticks !=0)
   {
	   Ticks--;
   }

}

void SystickInitialize()
{
	  // Update SystemCoreClock value
		SysTick->LOAD = (OSC / MILLIS_IN_SEC) -1;
	    // Configure the SysTick timer to overflow every 1 us
		//SysTick->CTRL = (1<<0) | (1<<1) | (1<<2);
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void DelayInit()
{
	SystickInitialize();
}

void DelayMs(uint32_t ms)
{
    // Wait until ms reach zero
	Ticks = ms;
    while(Ticks);
}
