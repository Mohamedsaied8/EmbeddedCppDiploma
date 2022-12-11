#include <stm32f10x.h> //include the Addresses of input and output Registers
long int i; //Loop Variable 
//0x40000000 
//0x20000 
//0x1000
#define RCC_BASE_  0x40021000
#define RCC_ ((RCC_Typedef *) RCC_BASE_)

int main(){
	
	RCC->APB2ENR =(1<<4) | (1<<2); //Enable Clock for PORTA and PORTC
	GPIOC->CRL =0x33333333; //make all pot c as output port
	
	while (1){
		
		GPIOC->ODR =0x000F; //output ones to all pins of PORT C
		GPIOC->ODR =0x0000; //output ones to all pins of PORT C

		//for(i=0;i<10000;i++); // dummy loop for delay to see the output 

}
	return 0;
}