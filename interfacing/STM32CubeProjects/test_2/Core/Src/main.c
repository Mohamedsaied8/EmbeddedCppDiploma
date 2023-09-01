#include "main.h"

//ISR
void EXTI4_IRQHandler(void)
{
  if ((EXTI->PR & (1<<4)) != 0) {                        // EXTI13 interrupt pending?
      EXTI->PR = EXTI_PR_PR4; // clear pending interrupt
      GPIOA->ODR ^=  (1 << 1);
  }

}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

	// enable clock for Alternate Function
	RCC->APB2ENR = (1<<0) | (1<<3) | (1<<2);
 	GPIOA->CRL = 0x33333333;
	GPIOB->CRL = 0x44444444;
	GPIOA->ODR =  (1 << 1);
    // Map EXTI4 to PB4
    AFIO->EXTICR[1] = (1<<0); //0x00000001

	EXTI->IMR       = (1 << 4) ;           // unmask interrupt
	EXTI->EMR       = (1 << 4) ;             // unmask event
	EXTI->RTSR      = (1 << 4) ;            // set rising edge
	//EXTI->FTSR       = (1 << 4) ;            // set falling edge
	NVIC->ISER[0] = (1<<10);

  while (1) {
	  // Loop forever

  } // end while
} // end main
