/* @file 			 : USART.h
*  @Description: This file includes the definitions of the USART used Addresses of Buses
*                Flags definitions , Registers structure , Baud Rate equation and USART DMA enable.
*	 @Author: 		 Mohamed Saied     & 			Mohamed Abdallah
*/
#ifndef USART_H
#define USART_H

#ifndef COMMON_H

#include "common.h"
#endif

#ifndef GPIO_H

#include "gpio.h"
#endif

#include <math.h>

#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define USART4_BASE           (APB1PERIPH_BASE + 0x4C00)
#define USART5_BASE           (APB1PERIPH_BASE + 0x5000)
#define USART1                ((USART_TypeDef  *) USART1_BASE  )
#define USART2                ((USART_TypeDef  *) USART2_BASE  )
#define USART3                ((USART_TypeDef  *) USART3_BASE  )
#define USART4                ((USART_TypeDef  *) USART4_BASE  )
#define USART5                ((USART_TypeDef  *) USART5_BASE  )

#define  USART_SR_PE                         ((uint16_t)0x0001)            /*!<Parity Error */
#define  USART_SR_FE                         ((uint16_t)0x0002)            /*!<Framing Error */
#define  USART_SR_NE                         ((uint16_t)0x0004)            /*!<Noise Error Flag */
#define  USART_SR_ORE                        ((uint16_t)0x0008)            /*!<OverRun Error */
#define  USART_SR_IDLE                       ((uint16_t)0x0010)            /*!<IDLE line detected */
#define  USART_SR_RXNE                       ((uint16_t)0x0020)            /*!<Read Data Register Not Empty */
#define  USART_SR_TC                         ((uint16_t)0x0040)            /*!<Transmission Complete */
#define  USART_SR_TXE                        ((uint16_t)0x0080)            /*!<Transmit Data Register Empty */
#define  USART_SR_LBD                        ((uint16_t)0x0100)            /*!<LIN Break Detection Flag */
#define  USART_SR_CTS       
/*********************************/
#define RCC_APB2ENR_USART1EN  1<<14
#define RCC_APB1ENR_USART2EN  1<<17
#define RCC_APB1ENR_USART3EN  1<<18
#define RCC_APB1ENR_USART4EN  1<<19
#define RCC_APB1ENR_USART5EN  1<<20
#define USART_CR1_RE          1<<2
#define USART_CR1_TE					1<<3
#define USART_CR1_UE				 	1<<13    
#define USART_DMA_EN          1<<7
#define USART_DMA_DIS         ~(1<<7)


/*----------------- Universal Synchronous Asynchronous Receiver Transmitter --*/
typedef struct
{
  __IO uint16_t SR;
       uint16_t RESERVED0;
  __IO uint16_t DR;
       uint16_t RESERVED1;
  __IO uint16_t BRR;
       uint16_t RESERVED2;
  __IO uint16_t CR1;
       uint16_t RESERVED3;
  __IO uint16_t CR2;
       uint16_t RESERVED4;
  __IO uint16_t CR3;
       uint16_t RESERVED5;
  __IO uint16_t GTPR;
       uint16_t RESERVED6;
} USART_TypeDef;


//Functions Prototypes
void usartInit(USART_TypeDef *usart,uint32_t br, int setremap);  
void Send_String(USART_TypeDef *uart,char *str);
unsigned char GetChar (USART_TypeDef *urt);
void sendChar (USART_TypeDef *uart,char ch);
void dma_read_usart1(char *data, int size);
void dma_write_usart1(char *data, int size);
void dma_read_usart2(char *data, int size);
void dma_write_usart2(char *data, int size);
void dma_read_usart3(char *data, int size);
void dma_write_usart3(char *data, int size);
void dma_read_usart4(char *data, int size);
void dma_write_usart4(char *data, int size);
#endif

