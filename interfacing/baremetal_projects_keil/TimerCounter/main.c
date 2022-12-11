/*
*This Project is an Example of using Timer 1 in Stm32f10x Series
*Author Mohamed Saied
*Date 27 April 2019

*/
#define CLOCK  	8000000 
#define LED_PIN		13
#include <stm32f10x.h>

unsigned long int counter;
void start_timer(TIM_TypeDef *TIMx, uint16_t ms) ;

int main(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //enable timer clock
	
	NVIC->ISER[0]=(1<<28); //enable nvic for timer2
	
	GPIOC->CRH=0x33333333;
	
	TIM2->SR =0; // status Reg
  TIM2->PSC = 10000;// 
	TIM2->ARR = 1000; //
	TIM2->EGR |= (1<<0); //UG

 // Enable the hardware interrupt.
  TIM2->DIER |= TIM_DIER_UIE; 
	TIM2->CR1 |= (1<<0);

	while(1){
		
	//counter=TIM2->CNT;
		/* Loop until the update event flag is set */
while (!(TIM2->SR & TIM_SR_UIF));
/* The required time delay has been elapsed */
/* User code can be executed */
		counter++;;
		if(counter>10000){
   //  GPIOC->ODR ^= (1 << LED_PIN);
			counter=0;
		}
	}
	return 0;
}
//Interrupt Service Routine
 
void TIM2_IRQHandler(void) {
  // Handle a timer 'update' interrupt event
  if (TIM2->SR & TIM_SR_UIF) {
    TIM2->SR &= ~(TIM_SR_UIF);
    // Toggle the LED output pin.
    GPIOC->ODR ^= (1 << LED_PIN);
  }
} 