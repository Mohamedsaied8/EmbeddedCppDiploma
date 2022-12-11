
#include <stm32f10x.h> // include the addresses of Registers from the Microcontroller Header File
#include <stdio.h>
#define ENABLE_GPIO_C     (1<<4)
long int i;
int main(){
	//Enable Clock for GPIOC from APB2ENR RCC(Reset Clock and Control module
	RCC->APB2ENR |=ENABLE_GPIO_C ;
	//Configuration [One Time]
	//PinC13 to be Output with High speed [3] 0x40011004
	GPIOC->CRH = 0x00300000; 
	
	while(1){
		// LOOOP
	//	GPIOC->ODR |= (1<<13); // Set PinC13 = 1
		for(i=0;i<100000;i++); //delay
		GPIOC->ODR &= ~(1<<13); // Reset PinC13 = 0
		for(i=0;i<100000;i++); //delay

		
	}
	
	return 0;
	
}