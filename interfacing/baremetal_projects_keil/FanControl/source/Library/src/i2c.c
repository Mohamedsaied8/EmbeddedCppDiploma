#include "i2c.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "semphr.h"


/*---------------------------------------------------------------------------*/
/** @brief I2C initialization.


@param[in] 
@param[in] 
*/
void I2CInit(I2C_TypeDef * I2CP,unsigned char rm){
	RCC->APB2ENR|=9;						//Enable AF & GPOPB
	if(I2CP==I2C1){
		RCC->APB1ENR |= 1<<21;					//Enable Clock for I2C1
		if(rm==1){			
			AFIO->MAPR   |= 1<<1;          //   set USART1 remap	
			GPIOB->CRH |= 0x000000FF;			//PB9,8 Open drain
		}
		else{
			GPIOB->CRL |= 0xFF000000;			//PB7,6 Open drain
		}				
	}
	else if(I2CP==I2C2){
		RCC->APB1ENR |= 1<<22;					//Enable Clock for I2C2
		GPIOB->CRH |= 0x0000FF00;				//PB11,10 Open drain
	}
	I2CP->CR1 = 0;							//disable I2C peripheral
	I2CP->CR2=(1<<3);						//8MHz HSI
	I2CP->CCR=40;							//40*125n=5000 ns *2(High & Low) =10,000 ns 1/10,000 = 100 KHz	I2C Freq
	I2CP->TRISE=9;							//Max rise time divided by 1/Freq +1
	I2CP->CR1 = 1;							//enable I2C peripheral	
}
/*---------------------------------------------------------------------------*/
/** @brief I2C error interrupt.


@param[in] 
@param[in] 
*/
void I2CErrorInterrupt(I2C_TypeDef * I2CP, char ITERREN){
	if(I2CP==I2C1) NVIC->ISER[1]|=(1<<0);
	if(I2CP==I2C2) NVIC->ISER[1]|=(1<<2);
	I2CP->CR1 &=~ (1<<8);							//disable I2C peripheral
	I2CP->CR2|=(ITERREN<<8);
	I2CP->CR1 |= (1<<0);							//enable I2C peripheral	
}

/*---------------------------------------------------------------------------*/
/** @brief I2C error interrupt.


@param[in] 
@param[in] 
*/
void I2CEventInterrupt(I2C_TypeDef * I2CP, char ITEVTEN){
//	if(I2CP==I2C1) NVIC->ISER[0]|=(1<<31);
	if(I2CP==I2C2) NVIC->ISER[1]|=(1<<1);
	I2CP->CR1 &=~ (1<<8);							//disable I2C peripheral
	I2CP->CR2|=(ITEVTEN<<9);
	I2CP->CR1 |= (1<<0);							//enable I2C peripheral	
}

/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.


@param[in] 
@param[in] 
*/
int I2C_Start(I2C_TypeDef * I2CP){
	unsigned int timeoutcount;
	I2CP->CR1 |= 1<<8;	//I2C Start
	for(timeoutcount=0;!(I2CP->SR1 & 0x0001);timeoutcount++){if(timeoutcount>10000){return -1;}}	//wait for start bit - see status register
	return 1;
}
/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.


@param[in] 
@param[in] 
*/
int I2C_Stop (I2C_TypeDef * I2CP){
	unsigned int timeoutcount;
	I2CP->CR1 |= 1<<9;
	for(timeoutcount=0;(I2CP->SR2 & 0x0002);timeoutcount++){if(timeoutcount>10000){return -1;}}	//wait for start bit - see status register
	return 1;
}
/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.


@param[in] 
@param[in] 
*/
 int I2C_Write (I2C_TypeDef * I2CP, unsigned char c){
	unsigned int timeoutcount;
	I2CP->DR = c;
	for(timeoutcount=0;!(I2CP->SR1 & (1<<7));timeoutcount++){if(timeoutcount>10000){return -1;}}	//wait for start bit - see status register
	return 1;
}
/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.


@param[in] 
@param[in] 
*/
int I2C_Addr (I2C_TypeDef * I2CP, unsigned char adr){
	unsigned int timeoutcount;
	I2CP->DR = adr | 0;	//Write to I2C Address register
	for(timeoutcount=0;!(I2CP->SR1 & 0x0002);timeoutcount++){if(timeoutcount>10000){return -1;}}	//wait for start bit - see status register
	I2CP->SR2;	//dummy read to clear - see status register 2
	return 1;
}
/*---------------------------------------------------------------------------*/
/** @brief Timer initialization.


@param[in] 
@param[in] 
*/
 int I2C_Read (I2C_TypeDef * I2CP, int ack){
	unsigned int timeoutcount;
	if (ack) I2CP->CR1 |= 0x0400;	//multiple bytes - set acknowledge bit in I2C_CR1
    else I2CP->CR1 &= ~0x0400;	//single or last byte clear ack bit
	for(timeoutcount=0;!(I2CP->SR1 & 0x00000040);timeoutcount++){if(timeoutcount>10000){return -1;}}	//wait for start bit - see status register
	return (I2CP->DR);
}

