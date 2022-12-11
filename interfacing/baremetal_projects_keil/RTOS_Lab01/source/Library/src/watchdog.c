#include "watchdog.h"
/*---------------------------------------------------------------------------*/
/** @brief Initialize WatchDog.

This Start WatchDog timer with reload value and prescaler 
PS
Independent WatchDog  has its own clock source with 32KHz.

@param[in] reload unsigned int. WatchDog timer reload value Value 0x00-0xFFF
@param[in] prescaler Unsigned int. Prescaler.
*/
void initWatchDog(unsigned int reload,char prescaler){
	IWDG->KR=0x5555;
	IWDG->RLR=reload;
	IWDG->PR=prescaler;
	IWDG->KR=0xCCCC;
	IWDG->KR=0xAAAA;
}
