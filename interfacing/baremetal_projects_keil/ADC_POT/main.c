/*
ADC Example 
*/
//#define STM32F10X_MD_VL
#include <stm32f10x.h>
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
void SystemInit (void){
	 Clock_72();
 }
//**********************************S
int main(){
	//Enable Clock for PORTC
//Enable Clock for ADC 1 & Alternate
		RCC->APB2ENR|= (1<<10) |(1<<4)|(1<<9)|(1<<2)|(1<<0);

	//Init GPIO
	GPIOC->CRH=0x00300000; //Output

	GPIOC->ODR|=(1<<13);
	while(1){
			//GPIOC->ODR&=~(1<<13);
	
	 Led_blinking(valX);
	sprintf(buffer,"%d,%d",valX,valY);
	Led_blinking(valY);

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