#ifndef IWDG_H
#define IWDG_H

#ifndef COMMON_H
#include "common.h"
#endif

#define PRESCALE_4 					0x0
#define PRESCALE_8 					0x1
#define PRESCALE_16 				0x2
#define PRESCALE_32 				0x3
#define PRESCALE_64 				0x4
#define PRESCALE_128 				0x5
#define PRESCALE_256 				0x6

#define resetWatchDog()	IWDG->KR=0xAAAA


#define IWDG                  ((IWDG_TypeDef   *) IWDG_BASE    )
/*------------------------ Independent Watchdog ------------------------------*/
typedef struct
{
  __IO uint32_t KR;
  __IO uint32_t PR;
  __IO uint32_t RLR;
  __IO uint32_t SR;
} IWDG_TypeDef;

void initWatchDog(unsigned int reload,char prescaler);
#endif
