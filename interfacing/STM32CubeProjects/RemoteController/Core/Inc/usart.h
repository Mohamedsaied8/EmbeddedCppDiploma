/*
 * usart.h
 *
 *  Created on: Dec 30, 2022
 *      Author: MMohamedSaid
 */

#ifndef INC_USART_H_
#define INC_USART_H_

class USART
{
public:

	typedef enum UsartIntance : uint32_t
	{
		Usart1 = USART1_BASE,
		Usart2 = USART2_BASE,
		Usart3 = USART3_BASE,

	};

	enum Baud : uint32_t
	{
		baud_9600 = 9600,
		baud_115200 = 115200
	};

	enum core
	{
		clock = 8000000
	};
	USART()
	{
		if(this == reinterpret_cast<USART*>(Usart1))
		{
			//Initialize USART1
		   //Enable clock for AFIO, USART1 and GPIOA
			RCC->APB2ENR = (1<<0) | (1<< 2) | (1<<14);

			//PA9 is Open-Drain for Transmission and PA10 is input floating
			GPIOA->CRH = (0x0B<<4) | (4<<8);

			//PA1 led is Output for Blue LED
			GPIOA->CRL = (3<<4);

			//Enable RE and TE from CR1 , M=0
			 CR1 = (1<<2) | (1<< 3);

			//Enable USART through UE
			CR1 |= (1<<13);


		}
	}

	void * operator new (size_t, UsartIntance usart)
	{
		return reinterpret_cast<void *>(usart);
	}
	//setters and getters for

	//set baud rate
	void setBaudRate(Baud baud)
	{
		//Baud rate = 9600
		double ubrr  = core::clock /baud;
		BRR = ubrr ;
	}
	//set in RX only

	//set in Tx

	//set number of Stop bits

	//set in interrupt mode

	//set enable DMA


	uint8_t recv()
	{
		while(!(SR & (1<<5)));
		return DR & 0x00FF;
	}

	void send(char data)
	{
		DR = data;
		while(!(SR & (1<<6)));
	}

	void sendString(char *str)
	{
		int i = 0;
		while(str[i] != '\0')
		{
			send(str[i]);
			i++;
		}
	}
private:
	 volatile uint32_t SR; //00
	 volatile uint32_t DR; //04
	 volatile uint32_t BRR;//08
	 volatile uint32_t CR1;//0c
	 volatile uint32_t CR2;//10
	 volatile uint32_t CR3;
	 volatile uint32_t GTPR;

};

#endif /* INC_USART_H_ */
