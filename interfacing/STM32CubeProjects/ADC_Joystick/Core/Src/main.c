/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int i=0;
int valX,valY;
char buffer[20];
//*********************
void Clock_72();
void Led_blinking(int long d);
int adcRead();
void adcInit_Ch1();
int adcRead_0();
void adcInit_Ch0();
//**************************
 //**********************************S
int main(){
	 Clock_72();

	//Enable Clock for PORTC & PORTA
	 //Enable Clock for ADC 1 & Alternate
	RCC->APB2ENR|= (1<<10) |(1<<4)|(1<<9)|(1<<2)|(1<<0);

	//Init GPIO
	GPIOC->CRH=0x00300000; //Output

    adcInit_Ch1();
	  adcInit_Ch0();

	GPIOC->ODR|=(1<<13);
	while(1){
			//GPIOC->ODR&=~(1<<13);
	 valX=adcRead();
	  Led_blinking(valX);
	valY=adcRead_0();
	//sprintf(buffer,"%d,%d",valX,valY);
	Led_blinking(valY*3);

	}
	return 0;
}
//**********************************S
void Led_blinking(int long d){
  	GPIOC->ODR&=~(1<<13);
	for(i=0;i<(d*30);i++);
	GPIOC->ODR|=(1<<13);
	for(i=0;i<(d*30);i++);
}
/******************************/
	void adcInit_Ch1(){
		//MODE:CFG Input=00 : Analog=00
		GPIOA->CRL=0x44444400;
		//ADC configure clock to 14Mhz
		RCC-> CFGR &= ~(3<<14);	//ensure ADCPRE is zero
		RCC-> CFGR |= (2<<14);  //14mHZ

		//A1configure pin for ADC as an input alternate
		//select Reqular Group from Control Register

		// Select the required Channel ADC12_IN1
		ADC1->SQR1|=0x00000180;
		ADC1->SQR2|=0;
		ADC1->SQR3|=0x00000001;
		//Sampling Time Selection ADC12_IN1 = PA1
		ADC1->SMPR1|=(6<<0);

		ADC1->CR2 |= (7<<17);	//select SWSTART as trigger
		ADC1->CR2 |= (1<<20);	//enable external trigger -

		//Right Alignment
		ADC1->CR2 &= ~(1<<11);	//right alignment -

		ADC1->CR2 |= (1<<1);	//continuous conversion
		//adc on
	   ADC1->CR2 |= (1<<0);	//ADC on

		ADC1->CR2 |= (1<<3);	// Reset calibration
		while (ADC1->CR2 & (1<<3));	// wait until reset finished
	   ADC1->CR2 |= (1<<2);	// start calibration
       while (ADC1->CR2 & (1<<2));	// wait until calibration finished

}


/******************************/
int adcRead(){
	 static int ADC_value=0;
	 ADC1->CR2 |= (1<<22); // start SW conversion
	 while (!(ADC1->SR & (1<<1)));	//EOC
	 ADC_value = ADC1->DR;
	//reset EOC Flag
	return ADC_value;
}
	//*******************************
void Clock_72(){
	FLASH->ACR	= 0x12;	//See note
	RCC->CR |= 1<<16;	//HSE on
	while (!(RCC->CR & (1<<17)));	//wait until HSE ready
	//  RCC->CFGR2 = 3<<4;	//Predev2 divide by 8 -->8MHz
	RCC->CR |= 1<<26;	//PLL2 on
	RCC->CFGR |= (1<<16);
	//  RCC->CFGR2 |= 3<<8;	//PLL2 multiply by 8->40MHz
	RCC->CFGR |= 7<<18;	// mult by 9	--->72MHz
	RCC->CFGR |= 1<<10;	//APB1 = 36MHz. See bus clocks.
	RCC->CR |= 1<<24;	//enable PLL
	while (!(RCC->CR & (1<<25)));	//wait until locked
	RCC->CFGR |= 2;	//PLL as clock source
}
//*******************************
void adcInit_Ch0(){
		//MODE:CFG Input=00 : Analog=00
		GPIOA->CRL|=0x44444400;
		//ADC configure clock to 14Mhz
		RCC-> CFGR &= ~(3<<14);	//ensure ADCPRE is zero
		RCC-> CFGR |= (2<<14);  //14mHZ

		//A1configure pin for ADC as an input alternate
		//select Reqular Group from Control Register

		// Select the required Channel ADC12_IN0
		ADC2->SQR1|=0x00000180;
		ADC2->SQR2|=0;
		ADC2->SQR3|=0x00000000;
		//Sampling Time Selection ADC12_IN0 = PA0 @ 1.5 cycles
		ADC2->SMPR1|=(6<<0);

		ADC2->CR2 |= (7<<17);	//select SWSTART as trigger
		ADC2->CR2 |= (1<<20);	//enable external trigger -

		//Right Alignment
		ADC2->CR2 &= ~(1<<11);	//right alignment -

		ADC2->CR2 |= (1<<1);	//continuous conversion
		//adc on
	  ADC2->CR2 |= (1<<0);	//ADC on

		ADC2->CR2 |= (1<<3);	// Reset calibration
    while (ADC2->CR2 & (1<<3));	// wait until reset finished
	  ADC2->CR2 |= (1<<2);	// start calibration
    while (ADC2->CR2 & (1<<2));	// wait until calibration finished

}
/******************************/
int adcRead_0(){
	static int ADC_value=0;
	 ADC2->CR2 |= (1<<22); // start SW conversion
	while (!(ADC2->SR & (1<<1)));	//EOC
	ADC_value = ADC2->DR;
	//reset EOC Flag
	ADC2->SR &= ~(1<<1);
	return ADC_value;
}
