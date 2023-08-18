/*
 * timer_driver.h
 *
 *  Created on: Jan 8, 2023
 *      Author: MMohamedSaid
 */

#ifndef INC_TIMER_DRIVER_H_
#define INC_TIMER_DRIVER_H_

#include "main.h"

class TIMER
{
public:
	//TIM1 = 0x40012C00
	//TIM1 and TIM8 are advanced timers
	typedef enum TimerInstance : uint32_t
	{
		TIM_1 = TIM1_BASE,
	};

	TIMER()
	{
		if(this == reinterpret_cast<TIMER*>(TimerInstance::TIM_1))
		{

		}
	}//CONSTRUCTOR

	//placement new overloading
	void* operator new(size_t, TimerInstance timer)
	{
		return reinterpret_cast <void*>(timer);
	}

	void pwmInit(unsigned int period)
	{
		// Enable alternate function clock. Bit 0 in RCC APB2ENR register
			RCC->APB2ENR |= (1 << 0) | (1 << 2)|(1 << 11);
			// Enable GPIOA clock
			// Enable clock for TIM1 clock. Bit 11 in RCC APB2ENR register

			// Make GPIOA Pin 11 (PA11) alternate-function output (0b1010)
			GPIOA->CRH &= 0xFFFF0FFF;
			GPIOA->CRH |= 0x0000B000;

			// PWM pin (defaults to PA11)
			// Reset CR1 just in case
			 CR1 = 0x0000;

			// Set prescaler
			// fCK_PSC / (PSC[15:0] + 1)
			// 72 Mhz / 71 + 1 = 1 Mhz timer clock speed
			 PSC = 71;
			// Set period to 20000
			 ARR = period;

			// Select pwm
			//Preload enable and PWM mode 1 for CH4
			 CCMR2 |= 0x6800;

			// Enable CH4 output and polarity active-high
			 CCER = 0x1000;

			// Enable Main Output
			 BDTR |= (1 << 15);

			//enable_interrupt(27);

			// Finally enable TIM1 module
			 CR1 |= (1 << 0);
	}
	void pwmWrite(unsigned int period,unsigned int duty){
 		unsigned int rawDuty= period * duty/100;
		 CCR4 = rawDuty;
	}
private:
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;


};

// PWM





#endif /* INC_TIMER_DRIVER_H_ */
