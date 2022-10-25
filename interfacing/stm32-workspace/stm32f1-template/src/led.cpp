extern "C"
{
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
}

#include "led.h"

LED::LED()
{
    Init_LED();
    LEDS_OFF();
}

void LED::LEDS_ON()
{
    GPIO_Write(GPIOC,0xF000);
    GPIO_Write(GPIOA,0x0004);

}
void LED::LEDS_OFF()
{
    GPIO_Write(GPIOC,0x0000);
    GPIO_Write(GPIOA,0x0000);
}

void LED::Init_LED()
 {
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    GPIO_InitTypeDef gpioLeds, gpioButton;
    gpioLeds.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_1;
    gpioLeds.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioLeds.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&gpioLeds);
    GPIO_Init(GPIOA,&gpioLeds);
   
    gpioButton.GPIO_Pin = GPIO_Pin_4;
    gpioButton.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
    gpioButton.GPIO_Pin = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&gpioButton);

 
    gpioLeds.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
    gpioLeds.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioLeds.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&gpioLeds);

    gpioButton.GPIO_Pin = GPIO_Pin_5;
    gpioButton.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&gpioButton);

}