#include "extint.h"
/*---------------------------------------------------------------------------*/
/** @brief External Interrupt Pin Enable.

This enable to choose which pin to enable in the external interrupt between pin 0 - 15.

@param[in] interrupt_number char. External interrupt number values 0-15
@param[in] pin char. pin number values 0-15.
*/
void EXTInterruptPinEnable(char interrupt_number,char pin){
  RCC->APB2ENR |= (1)|(1<<(pin+2));
  AFIO->EXTICR[(interrupt_number/4)]|=(pin<<(interrupt_number%4));
}
/** @brief External Interrupt Enable.

This enable external interrupt from 0 to 15 and allow to choose to interrupt
in rising edge or faling edge or both.

@param[in] interrupt_number char. External interrupt number values 0-15
@param[in] rising char. enable or disable interrupt at rising edge True or False.
@param[in] failing char. enable or disable interrupt at failing edge True or False.
*/
void EXTInterruptEnable(char interrupt_number,char rising,char failing){
	EXTI->IMR|=(1<<interrupt_number);
	EXTI->RTSR|=(rising<<interrupt_number);
	EXTI->FTSR|=(failing<<interrupt_number);
	
	if(interrupt_number<5){
		NVIC->ISER[0]|=(1<<(6+interrupt_number));
	}
	else if(interrupt_number>4&&interrupt_number<10){
		NVIC->ISER[0]|=1<<23;
	}
	else if(interrupt_number>10&&interrupt_number<16){
		NVIC->ISER[1]|=1<<8;
	}
}
/** @brief External Interrupt Disable.

This disable external interrupt from 0 to 15.

@param[in] interrupt_number char. External interrupt number values 0-15\
*/
void EXTInterruptDisable(char interrupt_number){
	EXTI->IMR&=~(1<<interrupt_number);
	EXTI->RTSR&=~(1<<interrupt_number);
	EXTI->FTSR&=~(1<<interrupt_number);	
	
	if(interrupt_number<5){
		NVIC->ISER[0]&=~(1<<(6+interrupt_number));
	}
	else if(interrupt_number>4&&interrupt_number<10){
		NVIC->ISER[0]&=~(1<<23);
	}
	else if(interrupt_number>10&&interrupt_number<16){
		NVIC->ISER[1]&=~(1<<8);
	}
}

/** @brief Reset External Interrupt.

This reset external interrupt from 0 to 15.

@param[in] interrupt_number char. External interrupt number values 0-15\
*/
void resetExternalInterrupt(char interrupt_number){
	EXTI->PR|=(1<<interrupt_number);
	EXTI->IMR|=(1<<interrupt_number);
}
