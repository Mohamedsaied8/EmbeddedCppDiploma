#include "buzzer.h"

hal::Buzzer::Buzzer(GPIO_TypeDef *GPIOx,uint32_t pin) :Buzzer_Port(GPIOx),
                                                        buzzer_pin(pin)
{   
    //initialization
    Buzzer_Init();
    Buzzer_Off();
}

void hal::Buzzer::Buzzer_On()
{
    //Buzzer_Port->ODR |= buzzer_pin;
    GPIO_SetBits(Buzzer_Port, buzzer_pin);
}

void hal::Buzzer::Buzzer_Off()
{
   // Buzzer_Port->ODR &=~buzzer_pin;
    GPIO_ResetBits(Buzzer_Port, buzzer_pin);

}
void hal::Buzzer::Buzzer_Init()
{
    // initialize clock for Buzzer Port
    setClock();
    // configure buzzer pin as an output pin
    GPIO_InitTypeDef gpioBuzzer;
    gpioBuzzer.GPIO_Pin = GPIO_Pin_9;
    gpioBuzzer.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioBuzzer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&gpioBuzzer);
}
void hal::Buzzer::setClock()
{
    if(Buzzer_Port == GPIOA)
    {
         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if(Buzzer_Port == GPIOB)
    {
         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
     if(Buzzer_Port == GPIOC)
    {
         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
}