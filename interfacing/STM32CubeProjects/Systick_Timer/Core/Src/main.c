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
/*
*This Project is an Example of using SysTick Timer in Stm32f10x Series
*Author Mohamed Saied
*Date 9 May 2019

*/

#include "delay.h"
unsigned int counter;
int main(){

	RCC->APB2ENR |= (1<<4); // Enable GPIOC
	GPIOC->CRH=0x33333333;
	DelayInit();

	while(1){

	 	GPIOC->ODR &=~(1<<13);
	 	DelayMs(1000);
		GPIOC->ODR |=(1<<13);
		DelayMs(1000);
	}
	return 0;
}


/*
*Function Delay
*/
