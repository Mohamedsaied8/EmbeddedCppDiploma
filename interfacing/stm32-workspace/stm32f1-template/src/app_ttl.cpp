/*
* establish communication with PC and MCu
* Baud rate 9600
* Enable Transmit and receive
* Polling
*/
#define FOSC 8000000
#define BAUD 9600
extern "C"
{
    #include "stm32f10x.h"
}
int main()
{
    //Enable clock for AFIO, USART1 and GPIOA
    RCC->APB2ENR = (1<<0) | (1<< 2) | (1<<14);

    //PA9 is Open-Drain for Transmission and PA10 is input floating
    GPIOA->CRH = (0x0B<<4) | (4<<8);
    
    //PA1 led is Output for Blue LED
    GPIOA->CRL = (3<<4);

    //Enable RE and TE from CR1 , M=0
    USART1->CR1 = (1<<2) | (1<< 3);
    //Baud rate = 9600
    double ubrr  = FOSC /BAUD;
    USART1->BRR = ubrr ;
    //Enable USART through UE
    USART1->CR1 |= (1<<13);

    while(1)
    {
      //check on receive flag
      while(!(USART1->SR & (1<<5))); 

      uint8_t control = USART1->DR & 0x00FF;

      if(control=='w')
      {
        //ON LED and delay for sometime
        GPIOA->ODR |= (1<<1);
        for(int i=0;i<1000;i++);
      }
      else{
          // OFF LED
        GPIOA->ODR &=~ (1<<1);

      }
    }

    return 0;
}