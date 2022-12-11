#pragma once
extern "C"
{
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
}

namespace hal{

    class Buzzer
    {
        public:
            Buzzer(GPIO_TypeDef *GPIOx, uint32_t pin);
            void Buzzer_Init();
            void Buzzer_On();
            void Buzzer_Off();
            void setClock();
        private:
        GPIO_TypeDef *Buzzer_Port;
        uint32_t buzzer_pin{0};
        uint32_t state{0};
    };
}

