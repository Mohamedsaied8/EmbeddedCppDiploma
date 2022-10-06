
#include "led.h"

struct LEDS
{
    void Init_LEDS();
};

void LEDS::Init_LEDS()
 {
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    //GPIOD->MODER |= 0x55000000;	//Bits 12..15 are output
    GPIO_InitTypeDef gpioLeds, gpioButton;
    gpioLeds.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 |GPIO_Pin_13;
    gpioLeds.GPIO_Mode = GPIO_Mode_Out_PP;
   // GPIO_Init_Port.GPIO_OType = GPIO_OType_PP;
    gpioLeds.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&gpioLeds);

    gpioLeds.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
    gpioLeds.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioLeds.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&gpioLeds);

    gpioButton.GPIO_Pin = GPIO_Pin_5;
    gpioButton.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&gpioButton);
}