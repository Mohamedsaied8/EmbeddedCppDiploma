#ifndef CLK_H
#define CLK_H

#ifndef COMMON_H
#include "common.h"
#endif
#define HSE 16
#define HSI 1
#define HSEON 17
#define HSION 2
#define PLL 24
#define PLLLOCKED 25
#define PLLMUL 18
#define APP1BCLK 10
#define PLLSCR 16
#define PSC1
#define CLKUPTO48 0x11
#define CLKUPTO72	0x12
#define PSC1

#ifdef Freq25
#define CYCLETIME 40
int __clk=25;
#endif
#ifdef Freq50
#define CYCLETIME 20
int __clk=50;
#endif
#ifdef Freq8
#define CYCLETIME 125
int __clk=8;
#endif

void initClk(void) __attribute__((always_inline));
void delayus(unsigned long __t) __attribute__((always_inline));
void delayms(unsigned long __t) __attribute__((always_inline));

/********************/
void initClk(){
#ifdef Freq25
  RCC->CR |= 1<<HSE;	//HSE on
  while (RCC->CR & (1<<HSEON));	//wait until HSE ready
  RCC->CFGR = 0x00000001;	//select HSE as system clock
  __clk=25;
 #endif
#ifdef Freq50
  FLASH->ACR = CLKUPTO72;  //for system clock between 48 and 72MHz
  RCC->CR |= 1<<HSE;  //HSE on  
  while (!(RCC->CR & (1<<HSEON)));  //wait until HSE ready 
  RCC->CFGR |= 2<<PLLMUL;  // mult by 9 --->72MHz  
  RCC->CFGR |= 1<<PLLSCR;  //APB1 = 36MHz. See bus clocks.  
  RCC->CFGR |= 1<<APP1BCLK;  //APB1 = 36MHz. See bus clocks.
  RCC->CR |= 1<<PLL;  //enable PLL  
  while (!(RCC->CR & (1<<PLLLOCKED)));  //wait until locked  
  RCC->CFGR |= 2;  //PLL as clock source  
  __clk=50;
#endif
#ifdef Freq8
  __clk=8;
#endif
}
void delayus(unsigned long __t){
  unsigned long __l=(((__t*1000)-(30*CYCLETIME))/(5*CYCLETIME));
	unsigned long __i=0;
    while(__i<__l){
			__nop();
        __i++;
	}
}
void delayms(unsigned long __t){
#ifdef Freq25
    unsigned long __l=((__t*5000)-6);
#endif
#ifdef Freq50
    unsigned long __l=((__t*10000)-6);
#endif
#ifdef Freq8
    unsigned long __l=((__t*1600)-6);
#endif
    unsigned long __i=0;
    while(__i<__l){
			__nop();
        __i++;
	}
}
#endif
