/*
    FreeRTOS V6.0.2 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS eBook                                  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

  
*/

/* Library includes. */
#include <string.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
 
/* Hardware specific headers. */
 
#include "SPI.h"
#include "usart.h"
/* Clock Configuration                  */
#define Freq8
#include "common.h"
#include "clk.h"


/*
 * Configure the processor for use with the Atmel demo board.  This is very
 * minimal as most of the setup is performed in the startup code.
 */
void clock_72(void);
static void prvSetupHardware( void );

/*
 * The idle hook is just used to stream data to the USB port.
 */
void vApplicationIdleHook( void );
/*-----------------------------------------------------------*/
void vApplicationStackOverflowHook( xTaskHandle *pxTask,signed char *pcTaskName );
/*
 * Setup hardware then start all the demo 
 application tasks.
 */

 
void task1(void *pvParameter);
xTaskHandle task1_Handler;

 

int main( void )
 {
	
	 prvSetupHardware();
 
	 xTaskCreate(task1,"task1",300,NULL,4,NULL);

 
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}
void task1(void *pvParameter){
	
	while(1){
		 Send_String(USART1,"task1 is Running");
	
		vTaskDelay(5000/portTICK_PERIOD_MS);
	
	}
	
}



static void prvSetupHardware( void )
{
	//clock_72();
  usartInit(USART1,9600,0);
	portInit(GPIOB,0xFFFF);


}

void clock_72(void)
{
FLASH->ACR	= 0x12;	//See note
RCC->CR |= 1<<16;	//HSE on
while (!(RCC->CR & (1<<17)));	//wait until HSE ready
RCC->CFGR2 = 4<<4;	//Predev2 divide by 5 -->5MHz
RCC->CFGR2 |= 6<<8;	//PLL2 multiply by 8->40MHz
RCC->CR |= 1<<26;	//PLL2 on
while (!(RCC->CR & (1<<27)));      	//wait until locked
RCC->CFGR2 |= (1<<16);	//PreDiv 2 as input
RCC->CFGR2 |= 4<<0;	//Prediv by 5	--->8MHz
RCC->CFGR |= (1<<16);	//PreDiv 1 as input
RCC->CFGR |= 7<<18;	// mult by 9	--->72MHz
RCC->CFGR |= 1<<10;	//APB1 = 36MHz. See bus clocks.
RCC->CR |= 1<<24;	//enable PLL
while (!(RCC->CR & (1<<25)));	//wait until locked
RCC->CFGR |= 2;	//PLL as clock source
	 
}


 

