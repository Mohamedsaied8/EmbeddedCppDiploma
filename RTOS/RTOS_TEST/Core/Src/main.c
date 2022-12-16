/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"


/*
 * Configure the processor for use with the Atmel demo board.  This is very
 * minimal as most of the setup is performed in the startup code.
 */
void clock_72(void);

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


	RCC->APB2ENR = (1<<4);
	GPIOC->CRH = (3<<20);
	xTaskCreate(task1,"task1",300,NULL,4,NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();
	while(1);
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}
void task1(void *pvParameter){

	while(1){

		GPIOC->ODR ^= (1<<13);
		vTaskDelay(150/portTICK_PERIOD_MS);

	}

}




void clock_72(void)
{
/*
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
*/
}
