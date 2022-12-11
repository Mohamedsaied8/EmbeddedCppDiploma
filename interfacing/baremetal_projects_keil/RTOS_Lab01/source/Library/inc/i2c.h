#ifndef I2C_H
#define I2C_H

#ifndef COMMON_H
#include "common.h"
#endif

#define REMAP	1
#define NOREMAP 0
#define ENABLE	1
#define DISABLE 0
#define ACKNOWLEDGE	1
#define NOACKNOWLEDGE 0

#define I2C1_BASE           					  (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE            						(APB1PERIPH_BASE + 0x5800)
#define I2C1                						((I2C_TypeDef *) I2C1_BASE)
#define I2C2                						((I2C_TypeDef *) I2C2_BASE)
#define enableI2C2Interrupt()						I2C2->CR2|=(1<<9)
#define disableI2C2Interrupt()					I2C2->CR2&=~(1<<9)
#define enableI2C2BufferInterrupt()			I2C2->CR2|=(1<<10)
#define disableI2C2BufferInterrupt()		I2C2->CR2&=~(1<<10)

typedef struct
{
  __IO uint16_t CR1;
  uint16_t  RESERVED0;
  __IO uint16_t CR2;
  uint16_t  RESERVED1;
  __IO uint16_t OAR1;
  uint16_t  RESERVED2;
  __IO uint16_t OAR2;
  uint16_t  RESERVED3;
  __IO uint16_t DR;
  uint16_t  RESERVED4;
  __IO uint16_t SR1;
  uint16_t  RESERVED5;
  __IO uint16_t SR2;
  uint16_t  RESERVED6;
  __IO uint16_t CCR;
  uint16_t  RESERVED7;
  __IO uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;


void I2CInit(I2C_TypeDef * I2CP,unsigned char rm);
void I2CErrorInterrupt(I2C_TypeDef * I2CP, char ITERREN);
void I2CEventInterrupt(I2C_TypeDef * I2CP, char ITEVTEN);
int I2C_Start(I2C_TypeDef * I2CP);
int I2C_Stop (I2C_TypeDef * I2CP);
int I2C_Write (I2C_TypeDef * I2CP, unsigned char c);
int I2C_Addr (I2C_TypeDef * I2CP, unsigned char adr);
int I2C_Read (I2C_TypeDef * I2CP, int ack);

#endif
