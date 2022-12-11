/*
 * By default 8 MHz internal clock is used (HSI)
 * Set up as 72 MHz (HSE-PLL)
 *
 * 8M   ->   *9   -> 72 MHz
 * HSE  -> PllMul -> System Clock
 * Set Prediv1Src = PLL2, Set PllSrc as Prediv1
 *
 * 8 MHz External clock is selected as the source clock (HSE)
 * It is multiplied by 9 with PllMul
 * Then choose Pll as the clock source
 */
 #include "Timer.h"


volatile uint32_t duty;
volatile uint32_t period;


void Clock_72(){
	FLASH->ACR	= 0x12;	//See note
	RCC->CR |= 1<<16;	//HSE on
	while (!(RCC->CR & (1<<17)));	//wait until HSE ready
  RCC->CR |= 1<<26;	//PLL2 on
	RCC->CFGR |= (1<<16);	
	RCC->CFGR |= 7<<18;	// mult by 9	--->72MHz
  RCC->CFGR |= 1<<10;	//APB1 = 36MHz. See bus clocks.
  RCC->CR |= 1<<24;	//enable PLL
	while (!(RCC->CR & (1<<25)));	//wait until locked
	RCC->CFGR |= 2;	//PLL as clock source
}

/*************************************************
* Main code starts from here
*************************************************/
int32_t main(void)
{
	
	period = 20000;
	// Set clock to 72 MHz
	Clock_72();

	Tim1_Init(period);
	

	while(1)
	{
		uint32_t j;
		uint16_t i;
		
			pwmWrite(period,50);
			for(j=0;j>9000000;j++);
	}

	// Should never reach here
	return 0;
}
