/*
 * This is an stm32f4 template program
 */

/* stm32f4_discovery.h is located in Utilities/STM32F4-Discovery
 * and defines the GPIO Pins where the leds are connected.
 * Including this header also includes stm32f4xx.h and
 * stm32f4xx_conf.h, which includes stm32f4xx_gpio.h
 */
#include "led.h"
extern "C"
{
//#include "stm32f4_discovery.h"
//#include "stm32f4xx_conf.h"
#include "stm32f10x.h"
}
void WaitMS();

/* Main function, the entry point of this program.
 * The main function is called from the startup code in file
 * Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s
 * (line 101)
 *       
 */
int main(void)
{  
    LED leds;

    while (1)
    { 
        if(!(GPIOB->IDR &(1<<3)))
        {
            WaitMS();   	
            leds.LEDS_ON();
            WaitMS();
      
        }
        else
        {
            leds.LEDS_OFF();
        }	


    }

    return 0; // never returns actually
}

void WaitMS()
{
       for(int i=0;i<100000;i++)
            __asm("nop");
}