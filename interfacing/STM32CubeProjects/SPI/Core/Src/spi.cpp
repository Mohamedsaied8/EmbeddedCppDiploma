/*
 * spi.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: MMohamedSaid
 */

#include "spi.h"
mcal::SPI::SPI()
{
	if(this == reinterpret_cast<SPI*>(SPI1Instance))
	{
		SPI1_Initialize();
	}
	if(this == reinterpret_cast<SPI*>(SPI2Instance))
	{
		SPI2_Initialize();
	}

}
void mcal::SPI::SPI1_Initialize()
{

}
void mcal::SPI::SPI2_Initialize()
{

}
void* mcal::SPI::operator new(unsigned int, mcal::SPIInstance spi)
{
	return reinterpret_cast<void*>(spi);
}
