#pragma once
extern "C"
{
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
}

class LED
{
public:
    LED(GPIO_TypeDef *GPIOx, uint16_t LED_PIN);
    void LED_ON();
    void LED_OFF();
    void LED_TOGGLE();
private:
    uint16_t LED_Pin{0};
    BitAction value{Bit_RESET};
    GPIO_TypeDef *GPIOx;
};