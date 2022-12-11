#ifndef __SPI_H
#define __SPI_H
#include "myspi.h"

//下面的定义3.50与3.22的库不一样
//----------------------------------------------


#define  SPInet_ReadWrite  SPI_ReadWriteByte
#define  SPInet_Init  		 SPI2_Init

//SPI1初始化
void SPI1_Init(void);
void SPI2_Init(void);

//SPI1读写一字节数据
unsigned char SPI_ReadWriteByte(unsigned char writedat);

//SPI2初始化
void SPI2_Init(void);
//SPI2读写一字节数据
//unsigned char SPI2_ReadWrite(unsigned char writedat);

#endif
