/*
 * This is an stm32f4 template program
 */

/* stm32f4_discovery.h is located in Utilities/STM32F4-Discovery
 * and defines the GPIO Pins where the leds are connected.
 * Including this header also includes stm32f4xx.h and
 * stm32f4xx_conf.h, which includes stm32f4xx_gpio.h
 */
#include "led.h"
#include "alarm.h"
extern "C"
{
#include "stm32f10x.h"
}

void WaitMS();


int main(void)
{  
     LED leds;
     hal::Buzzer buzzer(GPIOB,GPIO_Pin_9);
     Vehicle::Alarm alarm(&buzzer);

    while (1)
    { 
        
        if(!(GPIOB->IDR & (1<< 5))) // PB5 0000 0000 0010 0000
        {
            leds.LEDS_ON();
            alarm.setAlarm(true);
            WaitMS();
        }
        else
        {           
            alarm.setAlarm(false);
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
