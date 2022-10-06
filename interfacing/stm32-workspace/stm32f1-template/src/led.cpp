#include "led.h"

LED::LED( GPIO_TypeDef *GPIOx, uint16_t LED_PIN)
{
    if(GPIOx == GPIOA)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if(GPIOx == GPIOB)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if(GPIOx == GPIOC)
    {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }

    GPIO_InitTypeDef gpioLeds;
    gpioLeds.GPIO_Pin = LED_PIN;
    gpioLeds.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioLeds.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&gpioLeds);

}

void LED::LED_ON()
{
    GPIO_SetBits(GPIOx, LED_Pin);
}

void LED::LED_OFF()
{
    GPIO_ResetBits(GPIOx, LED_Pin);
}

void LED::LED_TOGGLE()
{
    value != value; 
    GPIO_WriteBit(GPIOx, LED_Pin, value);
}