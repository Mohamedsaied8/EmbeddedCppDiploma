/*
 * uart.h
 *
 *  Created on: Sep 5, 2023
 *      Author: MMohamedSaid
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#define USART1_BASE_ADDR 	0x40013800
#define USART2_BASE_ADDR 	0x40004400
#define USART3_BASE_ADDR 	0x40004800
#define FOSC       8000000
#define BAUD 		9600

enum UsartInstance
{
	USART1Instance = USART1_BASE_ADDR,
	USART2Instance = USART2_BASE_ADDR,
	USART3Instance = USART3_BASE_ADDR
};

enum FrameSize
{
	FrameSizeEight = 0,
	FrameSizeNine
};

class USART
{
public:
	USART(UsartInstance usart)
	{

		if(this == reinterpret_cast<USART*>(USART1Instance) )
		{

			//RCC enable clock gating for USART1
			Usart1Initialize();
		}
		else if(this == reinterpret_cast<USART*>(USART2))
		{

		}
	}

	void Usart1Initialize()
	{
		// Enable AFIO , GPIOA and USART1
		RCC->APB2ENR = (1<<0) | (1<<2) | (1<<14);
 		//PA9 to be Output alternate function for USART transmition
		GPIOA->CRH = (0x0B<<4); //1011
		//PA10 to be input floating for USART receive
		GPIOA->CRH |=(4<<8);
		double usart_div = FOSC / (BAUD);
		 BRR = usart_div;
		// Enable Transmission and Enable Reception
		 CR1 = (1<<2) | (1<<3);
		 CR1 |= (1<<13); // UE
	}
	void setFrameSize(FrameSize fsz)
	{
		CR1 = static_cast<uint32_t>(fsz);
	}

	char read()
	{
		while(! (SR & (1<<5)));
		return DR & 0x00FF;
	}
	void sendChar(char data)
	{
		DR = data & 0xFF;
		while(!(SR & (1<<7)));
	}
	void sendString(char *str)
	{
		int i =0;
		while(str[i] != '\0')
		{
			sendChar(str[i++]);
		}
	}
	void* operator new(size_t, UsartInstance usart)
	{
		return reinterpret_cast<void*>(0x40013800);
	}

private:
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;

};


#endif /* INC_UART_H_ */
