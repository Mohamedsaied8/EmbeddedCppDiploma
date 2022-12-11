/*
*MODULE : 7-SEGMENT
*AUTHOR : MOHAMED SAIED
*PINS : PIN1 GND PIN2 VCC PIN3 A PIN4 B PIN5 C PIN6 D ENABLE PINS:8 EN1 PIN9 EN2
*
*
*/
#include <stm32f10x.h>
	unsigned long long  i;
	unsigned int count;

int main(){
	


	//enable PORTA
	RCC->APB2ENR |= (1<<2)|(1<<4);
	GPIOA->CRL=0x33333333;
	GPIOC->CRH=0x33333333;
	GPIOC->ODR|=(1<<13);
	for(i=0;i<1000;i++);

	while(1){
		//count=0;
		switch(count){
			
			case 0: GPIOA->ODR =0x00;
							for(i=0;i<100000;i++);
						  count=1;
							break;

		 case 1: 
							//GPIOA->ODR &=~(1<<1) & ~(1<<2) & ~(1<<3);
							GPIOA->ODR =0x01;
							for(i=0;i<100000;i++);
							count++;
							break;
		
			case 2: GPIOA->ODR =0x02;
							for(i=0;i<100000;i++);
							count++;

							break;
			
			case 3: GPIOA->ODR =0x03;
							for(i=0;i<100000;i++);
							count++;

							break;
			
			case 4: GPIOA->ODR =0x04;
							for(i=0;i<100000;i++);
							count++;

							break;
							
			case 5: GPIOA->ODR =0x05;
							for(i=0;i<100000;i++);
							count++;
							break;
							
			case 6: GPIOA->ODR =0x06;
							for(i=0;i<100000;i++);
							count++;
							break;
							
		 case 7: GPIOA->ODR =0x07;
							for(i=0;i<100000;i++);
							count++;
							break;
							
	  	case 8: GPIOA->ODR =0x08;
							for(i=0;i<100000;i++);
							count++;
							break;
			case 9: GPIOA->ODR =0x09;
							for(i=0;i<100000;i++);
							count++;
							break;

		
			default:
							
						  count=0;
							break;			
		}
		
	}
	return 0;
}