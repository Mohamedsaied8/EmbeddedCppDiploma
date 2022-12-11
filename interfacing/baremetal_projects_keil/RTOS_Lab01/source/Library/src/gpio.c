#include "gpio.h"

/** @brief GPIO source file.

This source file should include functions to do the following 
@GPIO Initialize
@GPIO Read Input
@GPIO Write Output

*/

/*---------------------------------------------------------------------------*/
/** @brief GPIO PORT initialization.

This initialize the GPIO enables it's clock
*Specify the mode IN or OUT 
*specify disable AF
*Disable Pullups Resistors
*Enable Clock gating

@param[in] GPIOx. i.e GPIOA  @ref

@param[in] 16-bits value spevify the desired mode of each pin 1 for Output with max clock gating[50MHz] 0 for Input floating.

*/
void portInit(GPIO_TypeDef *GPIO,uint16_t __val){
unsigned long __y=0,__z=0;
	unsigned int __i,__p=0;
  int __bit_pos;
  Set_clock(GPIO);
 for(__i = 1, __bit_pos = 1; __i != 0 && __i <= 65535; __i <<= 1, __bit_pos++) {
  __p=4*(__bit_pos-1);
     if(__p<=31){   //set bit pos in 32 bits
       if(__val & __i){__y|=(3<<__p);}
       else{__y|=(4<<__p);}
			}
  if(__p>31){
     __p-=32;
    if(__val & __i){__z|=(3<<__p);}
	  else{	__z|=(4<<__p);}
  }
}

  GPIO->CRL=__y;
  GPIO->CRH=__z;
	
	
}
/** @brief GPIO PORT initialization Alternative Function (AF).

This initialize the GPIO enables it's clock
*Specify Enabling the Alternative Function (AF)for the desired GPIO pin 

@param[in] GPIOx. i.e GPIOA  @ref
@param[in] value wether the value was 1 then it's Output Push-Pull if 0 keep it as it was previously initialized 
*/
void portInitAlt(GPIO_TypeDef *GPIO,uint16_t _val){
unsigned long __y=0,__z=0;
	
// You can check the bit set positions of 16 bit integer.
// That's why the check is added "i != 0 && i <= val" to iterate till
// the end bit position.
unsigned int _i,_p=0;
int _bit_pos;
 	Set_clock(GPIO);
 for(_i = 1, _bit_pos = 1; _i != 0 && _i <= _val; _i <<= 1, _bit_pos++) {
  _p=4*(_bit_pos-1);
  if(_p<=31){  //set bit pos in 32 bits
    if(_val & _i){
  __y|=(11<<_p);
     }
  }
  if(_p>31){
  _p-=32;
    if(_val & _i){
  __z|=(11<<_p);

    }
                                
   }
  }
 GPIO->CRL=__y;
 GPIO->CRH=__z;
		
}
/** @brief GPIO PORT Write Output.

*Specify Output for the desired GPIO pin or many pins in the same GPIO

@param[in] GPIOx. i.e GPIOA  @ref

@param[in] value  Logic 0 or 1
*/
void portWrite(GPIO_TypeDef *GPIO,uint16_t value){
	GPIO->ODR=value;
}

void pinSet(GPIO_TypeDef *GPIO,uint16_t pinvalue){
	GPIO->BSRR=(1<<pinvalue);
}

void pinReset(GPIO_TypeDef *GPIO,uint16_t pinvalue){
	GPIO->BRR=(1<<pinvalue);
}


/** @brief GPIO PORT Read Input.

*Specify Output for the desired GPIO pin or many pins in the same GPIO

@param[in] GPIOx. i.e GPIOA  @ref

@param[in] pin position in the GPIO from [0 to 15]

@param[out] the return value Logic 0 or 1


*/
uint16_t portRead(GPIO_TypeDef *GPIO){
    return (GPIO->IDR);	
}

uint16_t pinRead(GPIO_TypeDef *GPIO,uint16_t pinvalue){
    return (GPIO->IDR)&(1<<pinvalue);	
}

/** @brief GPIO Set Clock.

*Specify Enabling the clock gating for the desired GPIO PORT

@param[in] GPIOx. i.e GPIOA  @ref

*/
void Set_clock(GPIO_TypeDef *GPIO)
{
	
    if(GPIO==GPIOA)
        {
        CLOCK_BUS2 |= PORTA_CLOCKEN;	// Enable GPIOE clock - necessary to use GPIOE

    }

        else if(GPIO==GPIOB)
        {
       CLOCK_BUS2 |= PORTB_CLOCKEN;	// Enable GPIOE clock - necessary to use GPIOE

    }
       else if(GPIO==GPIOC)
        {
        CLOCK_BUS2 |= PORTC_CLOCKEN;	// Enable GPIOE clock - necessary to use GPIOE

    }
				 else if(GPIO==GPIOD)
        {
        CLOCK_BUS2 |= PORTD_CLOCKEN;	// Enable GPIOE clock - necessary to use GPIOE

    }

         else if(GPIO==GPIOE)
        {
        CLOCK_BUS2 |= PORTE_CLOCKEN;	// Enable GPIOE clock - necessary to use GPIOE

    }
}
