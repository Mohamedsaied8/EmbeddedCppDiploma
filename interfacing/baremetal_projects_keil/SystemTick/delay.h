#ifndef _DELAY_H 
#define _DELAY_H
 
#include "stm32f10x.h"

void DelayInit();
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);

#endif