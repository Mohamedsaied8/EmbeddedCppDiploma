#ifndef EXTI_H
#define EXTI_H

#ifndef COMMON_H
#include "common.h"
#endif

#define EXTI                  ((EXTI_TypeDef   *) EXTI_BASE    )

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;


/* EXTI number definitions */
#define EXTI0				0
#define EXTI1				1
#define EXTI2				2
#define EXTI3				3
#define EXTI4				4
#define EXTI5				5
#define EXTI6				6
#define EXTI7				7
#define EXTI8				8
#define EXTI9				9
#define EXTI10				10
#define EXTI11				11
#define EXTI12				12
#define EXTI13				13
#define EXTI14				14
#define EXTI15				15
#define EXTI16				16
#define EXTI17				17
#define EXTI18				18
#define EXTI19				19
#define PA 					0
#define PB 					1
#define PC 					2
#define PD 					3
#define PE 					4

void EXTInterruptPinEnable(char interrupt_number,char pin);
void EXTInterruptEnable(char interrupt_number,char rising,char failing);
void EXTInterruptDisable(char interrupt_number);
void resetExternalInterrupt(char interrupt_number);
#endif
