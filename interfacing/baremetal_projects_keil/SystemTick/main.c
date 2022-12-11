/*
*This Project is an Example of using SysTick Timer in Stm32f10x Series
*Author Mohamed Saied
*Date 9 May 2019

*/

#include "delay.h"
unsigned int counter;
int main(){
	
	RCC->APB2ENR |= (1<<4);
	GPIOC->CRH=0x33333333;
	DelayInit();
//	SysTick->CTRL |= (1<<0) | (1<<1) | (1<<2);
//	SysTick->LOAD = 7999;

	while(1){
		
	 	GPIOC->ODR &=~(1<<13);
	 	DelayMs(1000);
		GPIOC->ODR |=(1<<13);
		DelayMs(1000);

	
	}
	return 0;
}


/*
*Function Delay
*/
