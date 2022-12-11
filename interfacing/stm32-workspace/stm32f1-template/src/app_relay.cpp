/*
* Testing Relay
*/
extern "C"
{
#include "stm32f10x.h"
}
void WaitMS();
constexpr uint8_t OUTPUT_50MHZ_SPEED = 3;
constexpr uint8_t FIRST_HALF_LIMIT = 7;

class Relay
{
    public:

    Relay(GPIO_TypeDef * port, uint32_t pin) : Relay_Port(port),Relay_Pin_Output(pin)
    {
        //total bits of the two registers = bits_crl + bits_crh = 64
        //pin 11 position in crh = ((11*4) - 32) = 12 
        Relay_Pin_Configuration = ((pin *4) -32);
        if(pin > FIRST_HALF_LIMIT)
        {
            Relay_Port->CRH |= (OUTPUT_50MHZ_SPEED << Relay_Pin_Configuration);
        }
        else
        {
            Relay_Port->CRL |= (OUTPUT_50MHZ_SPEED <<Relay_Pin_Configuration);
        }
    }
    void RelayON()
    {
       Relay_Port->ODR = (1<<Relay_Pin_Output);
    }
    void RelayOFF()
    {
        Relay_Port->ODR &= ~(1<<Relay_Pin_Output);
    }
    private:
    GPIO_TypeDef *Relay_Port;
    uint32_t Relay_Pin_Configuration;
    uint16_t Relay_Pin_Output;

};

int main(void)
{  
   constexpr uint8_t RELAY_PIN = 11; 
  //Enable Clock for GPIOB because is on PB11
    RCC->APB2ENR = (1<<3);
    GPIOB->CRH = 0x00000000;
    Relay lamb_relay(GPIOB,RELAY_PIN);
  //enable PB4 to be input pin works as button
    GPIOB->CRL = (4<<16);
    while (1)
    { 
        // check the state of the button
        if(!(GPIOB->IDR & (1<<4)))
        {   
            //RelayON
            lamb_relay.RelayON();
            WaitMS();
        }
        else
        {    
            lamb_relay.RelayOFF();
            //RELAY_OFF
        }

    }

    return 0; // never returns actually
}

void WaitMS()
{
       for(int i=0;i<100000;i++)
            __asm("nop");
}
