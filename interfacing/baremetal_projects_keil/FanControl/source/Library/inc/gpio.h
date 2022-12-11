#ifndef GPIO_H
#define GPIO_H


#ifndef COMMON_H

#include "common.h"
#endif
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;


#define GPIOA                 ((GPIO_TypeDef   *) GPIOA_BASE   )
#define GPIOB                 ((GPIO_TypeDef   *) GPIOB_BASE   )
#define GPIOC                 ((GPIO_TypeDef   *) GPIOC_BASE   )
#define GPIOD                 ((GPIO_TypeDef   *) GPIOD_BASE   )
#define GPIOE                 ((GPIO_TypeDef   *) GPIOE_BASE   )

/*******--PORTA---**************************/

#define PORTA								   GPIOA->ODR
#define BSRRA							     GPIOA->BSRR
#define PINA							     GPIOA->IDR
#define PORTA_MODEL						 GPIOA->CRL	
#define PORTA_MODEH 					 GPIOA->CRH
#define PORTA_BSRR						 GPIOA->BSRR
#define PORTA_BRR					   	 GPIOA->BRR
#define PORTA_LCKR						 GPIOA->LCKR

/*******--PORTB---**************************/

#define PORTB						  		 GPIOB->ODR
#define BSRRB						       GPIOB->BSRR
#define PINB						       GPIOB->IDR
#define PORTB_MODEL						 GPIOB->CRL	
#define PORTB_MODEH						 GPIOB->CRH
#define PORTB_BSRR						 GPIOB->BSRR
#define PORTB_BRR							 GPIOB->BRR
#define PORTB_LCKR						 GPIOB->LCKR

/*******--PORTC---**************************/

#define PORTC									 GPIOC->ODR 
#define BSRRC									 GPIOC->BSRR 
#define PINC									 GPIOC->IDR 
#define PORTC_MODEL						 GPIOC->CRL	
#define PORTC_MODEH						 GPIOC->CRH
#define PORTC_BSRR						 GPIOC->BSRR
#define PORTC_BRR							 GPIOC->BRR
#define PORTC_LCKR						 GPIOC->LCKR

/*******--PORTD---**************************/
#define PORTD									 GPIOD->ODR
#define BSRRD									 GPIOD->BSRR
#define PIND							  	 GPIOD->IDR
#define PORTD_CTRL						 GPIOD->CRL	
#define PORTD_CRH 						 GPIOD->CRH
#define PORTD_BSRR						 GPIOD->BSRR
#define PORTD_BRR							 GPIOD->BRR
#define PORTD_LCKR						 GPIOD->LCKR

/*******--PORTE---**************************/
#define PORTE									 GPIOE->ODR
#define BSRRE									 GPIOE->BSRR
#define PINE									 GPIOE->IDR
#define PORTE_MODEL						 GPIOE->CRL	
#define PORTE_MODEH 					 GPIOE->CRH
#define PORTE_BSRR						 GPIOE->BSRR
#define PORTE_BRR							 GPIOE->BRR
#define PORTE_LCKR						 GPIOE->LCKR

/********************************************/
#define CLOCK_BUS2                RCC->APB2ENR						
#define PORTA_CLOCKEN             1 << 2    //enable clock to port A
#define PORTB_CLOCKEN             1 << 3    //enable clock to port B
#define PORTC_CLOCKEN             1 << 4    //enable clock to port C
#define PORTD_CLOCKEN             1 << 5    //enable clock to port D
#define PORTE_CLOCKEN             1 << 6    //enable clock to port E
#define AFIO_CLOCKEN              1 << 0    //enable clock to AFIO
/********************************************/
//GPIO Data Structures
//Functions prototypes
void portInit(GPIO_TypeDef *GPIO,uint16_t __val);
void portInitAlt(GPIO_TypeDef *GPIO,uint16_t _val);
uint16_t portRead(GPIO_TypeDef *GPIO);
uint16_t pinRead(GPIO_TypeDef *GPIO,uint16_t pinvalue);
void Set_clock(GPIO_TypeDef *GPIO);
void portWrite(GPIO_TypeDef *GPIO,uint16_t value);
void pinSet(GPIO_TypeDef *GPIO,uint16_t pinvalue);
void pinReset(GPIO_TypeDef *GPIO,uint16_t pinvalue);
#endif

