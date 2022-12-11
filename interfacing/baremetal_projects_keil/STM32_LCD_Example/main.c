#include "stm32f10x.h"

#include "lcd.h"
 double i;
int main(void)
{
	RCC->APB2ENR|=(1<<4);
    InitializeLCD(); //Initialize LCD
    ClearLCDScreen(); //CLEAR LCD
    	GPIOC->CRH=0x33333333;
   Cursor(0,2); //Set Cursor to the First line second Character
  PrintStr("Embedded Group"); //Print String 
					delay(10);  

    while(1)
    {
			  Cursor(1,9); //Set Cursor to the First line second Character
				PrintStr("O7"); //Print String 
					delay(1000000);    
		
			

    }
}