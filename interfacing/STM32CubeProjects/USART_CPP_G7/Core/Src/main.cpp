//#include "main.h"
//#include "stm32f103xb.h"

#include "uart.h"

int main(void)
{
 	 USART *ble = new(USART1Instance) USART(USART1Instance);
 	 RCC->APB2ENR |= (1<<4);
 	 GPIOC->CRH = (3<<20);
 	 GPIOC->CRH |= (3<<24);
 	 while (1)
  {
	 char control= ble->read();
	  if( control == 'W')
	  {
		  ble->sendString("Front LED is ON\r\n");
		  GPIOC->ODR = (1<<13);
	  }
	  else if(control == 'w')
	  {
		  ble->sendString("Front LED is OFF\r\n");
		  GPIOC->ODR &=~ (1<<13);
	  }
	  else if(control == 'U')
	  {
		  ble->sendString("Back LED is ON\r\n");
		  GPIOC->ODR = (1<<14);
	  }
	  else if (control == 'u')
	  {
		  ble->sendString("Back LED is OFF\r\n");
		  GPIOC->ODR &=~ (1<<14);
	  }
	  else
	  {
		  ble->sendString("All LEDs are OFF\r\n");
		  GPIOC->ODR &=~ (1<<13);
		  GPIOC->ODR &=~ (1<<14);
	  }
  }

}
