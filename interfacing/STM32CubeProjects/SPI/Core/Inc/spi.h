/*
 * spi.h
 *
 *  Created on: Sep 23, 2023
 *      Author: MMohamedSaid
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
#include <stdint.h>

namespace mcal
{
	constexpr uint32_t SPI1_BASE_ADDRESS = 0x40013000;
	constexpr uint32_t SPI2_BASE_ADDRESS = 0x40003800;
	constexpr uint32_t SPI3_BASE_ADDRESS = 0x40003C00;

	enum SPIInstance
	{
		SPI1Instance = SPI1_BASE_ADDRESS,
		SPI2Instance = SPI2_BASE_ADDRESS,
		SPI3Instance = SPI3_BASE_ADDRESS
	};
	class SPI
	{
	public:
		SPI();
		~SPI();
	void SPI1_Initialize();
	void SPI2_Initialize();
	void * operator new(unsigned int, SPIInstance spi);
	private:
		//registers
	  volatile uint32_t CR1;
	  volatile uint32_t CR2;
	  volatile uint32_t SR;
	  volatile uint32_t DR;
	  volatile uint32_t CRCPR;
	  volatile uint32_t RXCRCR;
	  volatile uint32_t TXCRCR;
	  volatile uint32_t I2SCFGR;

	};
} //namespace mcal

#endif /* INC_SPI_H_ */
