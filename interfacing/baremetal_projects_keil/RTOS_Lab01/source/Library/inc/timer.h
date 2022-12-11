#ifndef TIMER_H
#define TIMER_H

#ifndef COMMON_H
#include "common.h"
#endif

#define INTERNAL                           						0
#define EM1                                						1
#define EM2                                						2
#define EM3                                						3
#define EXTERNAL                           						0x4000
#define RISING                             						0
#define FALLING                            						1
#define UP                                 						0
#define DOWN                               						1
#define DIRECTION                          						4
#define setTimerMax(TIMER,autoreload)      						TIMER->ARR =autoreload  
#define setTimerCount(TIMER,count)         						TIMER->CNT =count 
#define timerCount(TIMER)         										TIMER->CNT
#define reinitTimer(TIMER)                 						TIMER->EGR =1
#define resetTimerStatusUpdate(TIMER)            			TIMER->SR &= ~1
#define resetTimerStatusChannel(TIMER,channel)        TIMER->SR &= ~(1<<channel)
#define timerStatusUpdate(TIMER)					 						TIMER->SR & 1
#define timerStatusChannel(TIMER,channel)            	TIMER->SR &= (1<<channel)
#define readCaptureValueCH1(TIMER)										TIMER->CCR1
#define readCaptureValueCH2(TIMER)										TIMER->CCR2
#define readCaptureValueCH3(TIMER)										TIMER->CCR3
#define readCaptureValueCH4(TIMER)										TIMER->CCR4
#define micros()																			((MILLIS*1000)+(TIM6->CNT-1))

#define TIM2                  ((TIM_GP_TypeDef *) TIM2_BASE    )
#define TIM3                  ((TIM_GP_TypeDef *) TIM3_BASE    )
#define TIM4                  ((TIM_GP_TypeDef *) TIM4_BASE    )
#define TIM5                  ((TIM_GP_TypeDef *) TIM5_BASE    )
#define TIM6                  ((TIM_GP_TypeDef *) TIM6_BASE    )
#define TIM7                  ((TIM_GP_TypeDef *) TIM7_BASE    )

typedef struct
{
  __IO uint16_t CR1;
       uint16_t RESERVED0;
  __IO uint16_t CR2;
       uint16_t RESERVED1;
  __IO uint16_t SMCR;
       uint16_t RESERVED2;
  __IO uint16_t DIER;
       uint16_t RESERVED3;
  __IO uint16_t SR;
       uint16_t RESERVED4;
  __IO uint16_t EGR;
       uint16_t RESERVED5;
  __IO uint16_t CCMR1;
       uint16_t RESERVED6;
  __IO uint16_t CCMR2;
       uint16_t RESERVED7;
  __IO uint16_t CCER;
       uint16_t RESERVED8;
  __IO uint16_t CNT;
       uint16_t RESERVED9;
  __IO uint16_t PSC;
       uint16_t RESERVED10;
  __IO uint16_t ARR;
       uint16_t RESERVED11[3];
  __IO uint16_t CCR1;
       uint16_t RESERVED12;
  __IO uint16_t CCR2;
       uint16_t RESERVED13;
  __IO uint16_t CCR3;
       uint16_t RESERVED14;
  __IO uint16_t CCR4;
       uint16_t RESERVED15[3];
  __IO uint16_t DCR;
       uint16_t RESERVED16;
  __IO uint16_t DMAR;
       uint16_t RESERVED17;
} TIM_GP_TypeDef;

/*Function Prototypes*/
void timerInit(TIM_GP_TypeDef * TIMER,unsigned int prescaler);
void advancedTimerInit(TIM_GP_TypeDef * TIMER, unsigned int prescaler, unsigned int source, char dir);
void initTimerIC(TIM_GP_TypeDef * TIMER, char channel, char edge);
void initTimerOC(TIM_GP_TypeDef * TIMER, unsigned int period, unsigned int duty_cycle, char channel);
void initTimerOC4CH(TIM_GP_TypeDef * TIMER, unsigned int period, unsigned int chnnel1_duty_cycle, unsigned int chnnel2_duty_cycle, unsigned int chnnel3_duty_cycle, unsigned int chnnel4_duty_cycle);
unsigned int readCapture(TIM_GP_TypeDef * TIMER, char channel);
void enableTimerInterrupt(TIM_GP_TypeDef * TIMER, char update, char channel);
void disableTimerInterrupt(TIM_GP_TypeDef * TIMER, char channel);
void millisInit(void);
unsigned long millis(void);
void microsInit(void);
#endif
