#include "timer.h"
unsigned long MILLIS=0,MICROS=0;
/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.

This initialize the timer enable it's clock, enable alternative function clock, the 
clock to the GPIO, Select up counting mode and Internal Clock.
note this will set update event flag.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] prescaler Unsigned int. Prescaler values 0...0xFFFF.
*/
void timerInit(TIM_GP_TypeDef * TIMER,unsigned int prescaler){
	char timer_number;
	if(TIMER==TIM2) timer_number=2;
	else if(TIMER==TIM3) timer_number=3;
	else if(TIMER==TIM4) timer_number=4;
	else if(TIMER==TIM5) timer_number=5;
	
	RCC->APB1ENR |= (1<<(timer_number-2));     
  RCC->APB2ENR |= (1)|(1<<(timer_number-1));   
	TIMER->CR1 = 0x0000;	        
	TIMER->SMCR &= ~(0x07);           
 	TIMER->PSC = (prescaler-1); 	         
	TIMER->CR1 =1;	         
}
/*---------------------------------------------------------------------------*/
/** @brief Advanced timer initialization.

This initialize the timer enable it's clock, enable alternative function clock and
the clock to the GPIO, Allow you to Select counting mode and Clock Source.
note this will set update event flag.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] prescaler Unsigned int. Prescaler values 0...0xFFFF.
@param[in] source char. source values INTERNAL,EXTERNAL,EM1,EM2,EM3
@param[in] dir char. direction values UP or DOWN.
*/
void advancedTimerInit(TIM_GP_TypeDef * TIMER, unsigned int prescaler, unsigned int source, char dir){
	char timer_number;
	if(TIMER==TIM2) timer_number=2;
	else if(TIMER==TIM3) timer_number=3;
	else if(TIMER==TIM4) timer_number=4;
	else if(TIMER==TIM5) timer_number=5;
	
	RCC->APB1ENR |= (1<<(timer_number-2));     
  RCC->APB2ENR |= (1)|(1<<(timer_number-1));  
	TIMER->CR1 = 0x0000;	         
	TIMER->CR1 |= (dir<<DIRECTION);	        
	TIMER->SMCR &= ~(source);           
	TIMER->SMCR |= source;
 	TIMER->PSC = (prescaler-1); 
 	TIMER->CNT = 0; 	        
	TIMER->CR1 |= 0x01;          
}
/*---------------------------------------------------------------------------*/
/** @brief Initializetimer input capture.

This initialize one channel of a timer as input capture, Allow you to Select Edge detection
as rising or falling edge.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] channel char. channel values 1-4
@param[in] edge char. edge values RISING or FALLING.
*/
void initTimerIC(TIM_GP_TypeDef * TIMER, char channel, char edge){
	TIMER->CCER &= ~(1<<((channel-1)*4));
	if(edge ==RISING) TIMER->CCER &= ~(1<<(((channel-1)*4)+1));
	else TIMER->CCER |= (1<<(((channel-1)*4)+1));
	if(channel<3){ 
	  TIMER->CCMR1 &= ~(3<<((channel-1)*8));
	  TIMER->CCMR1 |= (1<<((channel-1)*8));
	}
	else{ 
	  TIMER->CCMR2 &= ~(3<<((channel-3)*8));
	  TIMER->CCMR2 |= (1<<((channel-3)*8));
	}		
	TIMER->CCER |= (1<<((channel-1)*4));
}
/*---------------------------------------------------------------------------*/
/** @brief Initializetimer output compare.

This initialize one channel of a timer as output compare to use as PWM, Allow you to Select
the peroid of the PWM and it's duty cycle.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] period Unsigned int. period values 0...0xFFFF.
@param[in] duty_cycle Unsigned int. duty_cycle values 0...0xFFFF.
@param[in] channel char. channel values 1-4
*/
void initTimerOC(TIM_GP_TypeDef * TIMER, unsigned int period, unsigned int duty_cycle, char channel)
	{
	TIMER->CCER &= ~(1<<((channel-1)*4));
	TIMER->ARR = period;
	if(channel<3){ 
	  TIMER->CCMR1 &= ~(0xff<<((channel-1)*8));
	  TIMER->CCMR1 |= (0x68<<((channel-1)*8));
	}
	else{ 
	  TIMER->CCMR2 &= ~(0xff<<((channel-3)*8));
	  TIMER->CCMR2 |= (0x68<<((channel-3)*8));  }

 	switch(channel){
		case 1: TIMER->CCR1=duty_cycle;break;
		case 2: TIMER->CCR2=duty_cycle;break;
		case 3: TIMER->CCR3=duty_cycle;break;
		case 4: TIMER->CCR4=duty_cycle;break;
	}		
	TIMER->CCER |= (1<<((channel-1)*4));
}
/** @brief Initializetimer output compare for the 4 channels.

This initialize thr four channel of a timer as output compare to use as PWM, Allow you to Select
the peroid of the PWM and it's duty cycle.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] period Unsigned int. period values 0...0xFFFF.
@param[in] duty_cycle1 Unsigned int. duty_cycle1 values 0...0xFFFF.
@param[in] duty_cycle2 Unsigned int. duty_cycle2 values 0...0xFFFF.
@param[in] duty_cycle3 Unsigned int. duty_cycle3 values 0...0xFFFF.
@param[in] duty_cycle4 Unsigned int. duty_cycle4 values 0...0xFFFF.
*/
void initTimerOC4CH(TIM_GP_TypeDef * TIMER, unsigned int period, unsigned int chnnel1_duty_cycle, unsigned int chnnel2_duty_cycle, unsigned int chnnel3_duty_cycle, unsigned int chnnel4_duty_cycle){
	TIMER->CCER &= ~(0xff);
	TIMER->ARR = period;
	TIMER->CCMR1 = 0x6868;
	TIMER->CCMR2 = 0x6868;
	TIMER->CCR1=chnnel1_duty_cycle;
	TIMER->CCR2=chnnel2_duty_cycle;
	TIMER->CCR3=chnnel3_duty_cycle;
	TIMER->CCR4=chnnel4_duty_cycle;		
	TIMER->CCER =0x1111;
}
/*---------------------------------------------------------------------------*/
/** @brief Read input capture value.

This wait until the input capture detect edge and input capture store the timer
value in Capture Compare Register CCR and return its value.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] channel char. channel values 1-4
@param[out] value unsigned int. values 0...0xFFFF
*/

unsigned int readCapture(TIM_GP_TypeDef * TIMER, char channel){
	while (!(TIMER->SR &(1<<channel)));     //wait - 
  TIMER->SR &= ~(1<<channel);	//clear flag
	switch(channel){
		case 1: return (TIMER->CCR1);            //capture-compare register
		case 2: return (TIMER->CCR2);            //capture-compare register
		case 3: return (TIMER->CCR3);            //capture-compare register
		case 4: return (TIMER->CCR4);            //capture-compare register	
	}
	return 0;
}
/*---------------------------------------------------------------------------*/
/** @brief Enable  timer  interrupt.

This enable timer interrupt for one channel giving you the choise to enable or disable
update event interrupt.

note:
to enable or disable update event interrupt only set channel to 0

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] update char. update values 0 or 1.
@param[in] channel char. channel values 1-4
*/
void enableTimerInterrupt(TIM_GP_TypeDef * TIMER, char update, char channel){
  if (update==1) TIMER->DIER |= 0x01;       
  else TIMER->DIER &= ~(0x01);       
  if(channel!=0) TIMER->DIER |= 1<<channel;    
  if(TIMER==TIM2) NVIC->ISER[0] |= 1<<28;     
	else if(TIMER==TIM3) NVIC->ISER[0] |= 1<<29;     
	else if(TIMER==TIM4) NVIC->ISER[0] |= 1<<30;   
	else if(TIMER==TIM5) NVIC->ISER[1] |= 1<<18;     
}
/*---------------------------------------------------------------------------*/
/** @brief Disable  timer  interrupt.

This disable timer interrupt for one channel.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] channel char. channel values 1-4
*/
void disableTimerInterrupt(TIM_GP_TypeDef * TIMER, char channel){
  if(channel!=0) TIMER->DIER &= ~(1<<channel);    
  if(TIMER==TIM2) NVIC->ISER[0] &= ~(1<<28);     
	else if(TIMER==TIM3) NVIC->ISER[0] &= ~(1<<29);     
	else if(TIMER==TIM4) NVIC->ISER[0] &= ~(1<<30);   
	else if(TIMER==TIM5) NVIC->ISER[1] &= ~(1<<18);     
}
/*---------------------------------------------------------------------------*/
/** @brief Millis initialization.

This initialize the timer 6 enable it's clock, Select up counting mode and Internal Clock.
note this will set update event flag.

@param[in] TIMER TIM_GP_TypeDef. Timer register address base @ref
TIMx_BASE
@param[in] prescaler Unsigned int. Prescaler values 0...0xFFFF.
*/
void millisInit(){
	RCC->APB1ENR |= (1<<(4));     
	TIM6->CR1 = 0x0000;	        
	TIM6->SMCR &= ~(0x07);           
 	TIM6->PSC = 7;
	TIM6->ARR=999;
	TIM6->CR1 =1;	
	TIM6->DIER |= 0x01;
  NVIC->ISER[1] |= 1<<22;	
}
/*---------------------------------------------------------------------------*/
/*
void TIM6_IRQHandler(){
	if(TIM6->SR & 1){
	  MILLIS+=1 ;
	  TIM6->SR &= ~1;
	}
}*/
/*---------------------------------------------------------------------------*/
unsigned long millis(){
	return MILLIS;
}
