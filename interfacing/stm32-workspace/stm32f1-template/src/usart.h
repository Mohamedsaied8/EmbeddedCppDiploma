#pragma once
extern "C"
{
#include <stdlib.h>
#include "stm32f10x.h"
}

enum class Usart_n
{
    usart1 = 0,
    usart2 = 1,
    usart3 = 2
};
class USART
{
    public:

    typedef enum UsartInstance : uint32_t
    {
        Usart1 = USART1_BASE,
        Usart2 = USART2_BASE,
        Usart3 = USART3_BASE
    };

    enum Parity : uint8_t 
    {
       ParityEven = 0x00,
       ParityOdd = 0x01
    };


private:

    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;

    public:

    USART()
    {
       if (this == reinterpret_cast<USART *>(Usart1))
       {
           // enable clock for GPIOA and USART1
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

            // reset pin configurations for PA9 and PA10
            GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

            // PA9 as Output@50Hz Alternate function
            GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

            // PA10 as floating input
            GPIOA->CRH |= GPIO_CRH_CNF10_0;
       }
    }

    ~USART()
    {
        if (this == reinterpret_cast<USART *>(Usart1))
        {
            // disable clock for USART1 peripheral
            RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
        }
    }

    /**
     * @brief Get reference to a USART instance
     *
     * @param usart required hardware usart instance
     * @return void* pointer to the USART object
     */
    void *operator new(size_t, UsartInstance usart)
    {
        return reinterpret_cast<void *>(usart);
    }
    


};