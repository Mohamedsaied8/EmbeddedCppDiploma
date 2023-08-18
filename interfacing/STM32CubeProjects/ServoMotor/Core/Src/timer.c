/*
 * timer.c
 *
 *  Created on: Jan 6, 2023
 *      Author: MMohamedSaid
 */


#include "Timer.h"
void Tim1_Init(unsigned int period ){
	// Enable alternate function clock. Bit 0 in RCC APB2ENR register
	RCC->APB2ENR |= (1 << 0) | (1 << 2)|(1 << 11);
	// Enable GPIOA clock
	// Enable clock for TIM1 clock. Bit 11 in RCC APB2ENR register

	// Make GPIOA Pin 11 (PA11) alternate-function output (0b1010)
	GPIOA->CRH &= 0xFFFF0FFF;
	GPIOA->CRH |= 0x0000B000;

	// PWM pin (defaults to PA11)
	// Reset CR1 just in case
	TIM1->CR1 = 0x0000;

	// Set prescaler
	// fCK_PSC / (PSC[15:0] + 1)
	// 72 Mhz / 71 + 1 = 1 Mhz timer clock speed
	TIM1->PSC = 71;
	// Set period to 20000
	TIM1->ARR = period;
	// Set duty cycle
	//TIM1->CCR4 = duty;

	// Enable Capture/Compare 4 interrupt
	//TIM1->DIER = (1 << 4);

	// Select pwm
	//Preload enable and PWM mode 1 for CH4
	TIM1->CCMR2 |= 0x6800;

	// Enable CH4 output and polarity active-high
	TIM1->CCER = 0x1000;

	// Enable Main Output
	 TIM1->BDTR |= (1 << 15);

	//enable_interrupt(27);

	// Finally enable TIM1 module
	TIM1->CR1 |= (1 << 0);
}


//***************************
void pwmWrite(unsigned int period,unsigned int duty){
		// 20000 * 1 / 100 =
	unsigned int rawDuty= period * duty/100;
	TIM1->CCR4=rawDuty;
}

/*
 * Enable given interrupt
 *
 * Each ISER {0-7} holds 32 interrupts. Thus take mod32 of the given interrupt
 *   to choose the ISER number (ISER[0] for IRQn 0-31, and ISER[1] for IRQn 32-63 ..)
 *   Then, enable the given bit on that register based on the remainder of the mod.
 */
void enable_interrupt(IRQn_Type IRQn)
{
	NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/*
 * Disable given interrupt
 */
void disable_interrupt(IRQn_Type IRQn)
{
	NVIC->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

