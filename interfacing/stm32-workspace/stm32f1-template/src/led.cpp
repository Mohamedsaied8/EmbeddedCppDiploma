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

}
void LED::LEDS_OFF()
{
    GPIO_Write(GPIOC,0x0000);
}

void LED::Init_LED()
 {
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    //GPIOD->MODER |= 0x55000000;	//Bits 12..15 are output
    GPIO_InitTypeDef gpioLeds, gpioButton;
    gpioLeds.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 |GPIO_Pin_13 | GPIO_Pin_12;
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