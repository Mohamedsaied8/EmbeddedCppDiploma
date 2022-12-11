#ifndef	SPI_H
#define SPI_H

#ifndef COMMON_H

#include "common.h"
#endif

#ifndef GPIO_H

#include "gpio.h"
#endif
 #ifndef DMA_H

#include "dma.h"
#endif
 #ifndef NVIC_H

#include "nvic.h"
#endif


#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)
typedef struct
{
  __IO uint16_t CR1;
  uint16_t  RESERVED0;
  __IO uint16_t CR2;
  uint16_t  RESERVED1;
  __IO uint16_t SR;
  uint16_t  RESERVED2;
  __IO uint16_t DR;
  uint16_t  RESERVED3;
  __IO uint16_t CRCPR;
  uint16_t  RESERVED4;
  __IO uint16_t RXCRCR;
  uint16_t  RESERVED5;
  __IO uint16_t TXCRCR;
  uint16_t  RESERVED6;
  __IO uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  __IO uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;


#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)



/* BIDIMODE: Bidirectional data mode enable */
#define SPI_CR1_BIDIMODE_2LINE_UNIDIR	(0 << 15)
#define SPI_CR1_BIDIMODE_1LINE_BIDIR	(1 << 15)
#define SPI_CR1_BIDIMODE		(1 << 15)

/* BIDIOE: Output enable in bidirectional mode */
#define SPI_CR1_BIDIOE			(1 << 14)

/* CRCEN: Hardware CRC calculation enable */
#define SPI_CR1_CRCEN			(1 << 13)

/* CRCNEXT: Transmit CRC next */
#define SPI_CR1_CRCNEXT			(1 << 12)

/* RXONLY: Receive only */
#define SPI_CR1_RXONLY			(1 << 10)

/* SSM: Software slave management */
#define SPI_CR1_SSM			(1 << 9)

/* SSI: Internal slave select */
#define SPI_CR1_SSI			(1 << 8)

/* LSBFIRST: Frame format */
/****************************************************************************/
/** @defgroup spi_lsbfirst SPI lsb/msb first
@ingroup spi_defines
@{*/
#define SPI_CR1_MSBFIRST		(0 << 7)
#define SPI_CR1_LSBFIRST		(1 << 7)
/**@}*/

/* SPE: SPI enable */
#define SPI_CR1_SPE			(1 << 6)

/* BR[2:0]: Baud rate control */
/****************************************************************************/
/** @defgroup spi_baudrate SPI peripheral baud rates
@ingroup spi_defines
@{*/
#define SPI_CR1_BAUDRATE_FPCLK_DIV_2	(0x00 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_4	(0x01 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_8	(0x02 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_16	(0x03 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_32	(0x04 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_64	(0x05 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_128	(0x06 << 3)
#define SPI_CR1_BAUDRATE_FPCLK_DIV_256	(0x07 << 3)
/**@}*/
/****************************************************************************/
/** @defgroup spi_br_pre SPI peripheral baud rate prescale values
@ingroup spi_defines
@{*/
#define SPI_CR1_BR_FPCLK_DIV_2		0x0
#define SPI_CR1_BR_FPCLK_DIV_4		0x1
#define SPI_CR1_BR_FPCLK_DIV_8		0x2
#define SPI_CR1_BR_FPCLK_DIV_16		0x3
#define SPI_CR1_BR_FPCLK_DIV_32		0x4
#define SPI_CR1_BR_FPCLK_DIV_64		0x5
#define SPI_CR1_BR_FPCLK_DIV_128	0x6
#define SPI_CR1_BR_FPCLK_DIV_256	0x7
/**@}*/

/* MSTR: Master selection */
#define SPI_CR1_MSTR			(1 << 2)

/* CPOL: Clock polarity */
/****************************************************************************/
/** @defgroup spi_cpol SPI clock polarity
@ingroup spi_defines
@{*/
#define SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE	(0 << 1)
#define SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE	(1 << 1)
/**@}*/
#define SPI_CR1_CPOL			(1 << 1)

/* CPHA: Clock phase */
/****************************************************************************/
/** @defgroup spi_cpha SPI clock phase
@ingroup spi_defines
@{*/
#define SPI_CR1_CPHA_CLK_TRANSITION_1	(0 << 0)
#define SPI_CR1_CPHA_CLK_TRANSITION_2	(1 << 0)
/**@}*/
#define SPI_CR1_CPHA			(1 << 0)

/* --- SPI_CR2 values ------------------------------------------------------ */

/* Bits [15:8]: Reserved. Forced to 0 by hardware. Used on F3. */

/* TXEIE: Tx buffer empty interrupt enable */
#define SPI_CR2_TXEIE			(1 << 7)

/* RXNEIE: Rx buffer not empty interrupt enable */
#define SPI_CR2_RXNEIE			(1 << 6)

/* ERRIE: Error interrupt enable */
#define SPI_CR2_ERRIE			(1 << 5)

/* Bits [4:3]: Reserved. Forced to 0 by hardware. */

/* SSOE: SS output enable */
/* Note: Not used in I2S mode. */
#define SPI_CR2_SSOE			(1 << 2)

/* TXDMAEN: Tx buffer DMA enable */
#define SPI_CR2_TXDMAEN			(1 << 1)

/* RXDMAEN: Rx buffer DMA enable */
#define SPI_CR2_RXDMAEN			(1 << 0)

/* --- SPI_SR values ------------------------------------------------------- */

/* Bits [15:8]: Reserved. Forced to 0 by hardware. Used on F3. */

/* BSY: Busy flag */
#define SPI_SR_BSY			(1 << 7)

/* OVR: Overrun flag */
#define SPI_SR_OVR			(1 << 6)

/* MODF: Mode fault */
/* Note: Not used in I2S mode. */
#define SPI_SR_MODF			(1 << 5)

/* CRCERR: CRC error flag */
/* Note: Not used in I2S mode. */
#define SPI_SR_CRCERR			(1 << 4)

/* UDR: Underrun flag */
/* Note: Not used in SPI mode. */
#define SPI_SR_UDR			(1 << 3)

/* CHSIDE: Channel side */
/* Note: Not used in SPI mode. No meaning in PCM mode. */
#define SPI_SR_CHSIDE			(1 << 2)

/* TXE: Transmit buffer empty */
#define SPI_SR_TXE			(1 << 1)

/* RXNE: Receive buffer not empty */
#define SPI_SR_RXNE			(1 << 0)

/* --- SPI_DR values ------------------------------------------------------- */

/* SPI_DR[15:0]: Data Register. */

/* --- SPI_CRCPR values ---------------------------------------------------- */

/* Note: Not used in I2S mode. */
/* SPI_CRCPR [15:0]: CRC Polynomial Register. */

/* --- SPI_RXCRCR values --------------------------------------------------- */

/* Note: Not used in I2S mode. */
/* SPI_RXCRCR [15:0]: RX CRC Register. */

/* --- SPI_TXCRCR values --------------------------------------------------- */

/* Note: Not used in I2S mode. */
/* SPI_TXCRCR [15:0]: TX CRC Register. */

/* --- SPI_I2SCFGR values -------------------------------------------------- */

/* Note: None of these bits are used in SPI mode. */

/* Bits [15:12]: Reserved. Forced to 0 by hardware. */

/* I2SMOD: I2S mode selection */
#define SPI_I2SCFGR_I2SMOD			(1 << 11)

/* I2SE: I2S enable */
#define SPI_I2SCFGR_I2SE			(1 << 10)

/* I2SCFG[9:8]: I2S configuration mode */
#define SPI_I2SCFGR_I2SCFG_LSB			8
#define SPI_I2SCFGR_I2SCFG_SLAVE_TRANSMIT	0x0
#define SPI_I2SCFGR_I2SCFG_SLAVE_RECEIVE	0x1
#define SPI_I2SCFGR_I2SCFG_MASTER_TRANSMIT	0x2
#define SPI_I2SCFGR_I2SCFG_MASTER_RECEIVE	0x3

/* PCMSYNC: PCM frame synchronization */
#define SPI_I2SCFGR_PCMSYNC			(1 << 7)

/* Bit 6: Reserved. Forced to 0 by hardware. */

/* I2SSTD[5:4]: I2S standard selection */
#define SPI_I2SCFGR_I2SSTD_LSB			4
#define SPI_I2SCFGR_I2SSTD_I2S_PHILIPS		0x0
#define SPI_I2SCFGR_I2SSTD_MSB_JUSTIFIED	0x1
#define SPI_I2SCFGR_I2SSTD_LSB_JUSTIFIED	0x2
#define SPI_I2SCFGR_I2SSTD_PCM			0x3

/* CKPOL: Steady state clock polarity */
#define SPI_I2SCFGR_CKPOL			(1 << 3)

/* DATLEN[2:1]: Data length to be transferred */
#define SPI_I2SCFGR_DATLEN_LSB			1
#define SPI_I2SCFGR_DATLEN_16BIT		0x0
#define SPI_I2SCFGR_DATLEN_24BIT		0x1
#define SPI_I2SCFGR_DATLEN_32BIT		0x2

/* CHLEN: Channel length */
#define SPI_I2SCFGR_CHLEN			(1 << 0)

/* --- SPI_I2SPR values ---------------------------------------------------- */

/* Note: None of these bits are used in SPI mode. */

/* Bits [15:10]: Reserved. Forced to 0 by hardware. */

/* MCKOE: Master clock output enable */
#define SPI_I2SPR_MCKOE				(1 << 9)

/* ODD: Odd factor for the prescaler */
#define SPI_I2SPR_ODD				(1 << 8)

/* I2SDIV[7:0]: I2S linear prescaler */
/* 0 and 1 are forbidden values */
#define SPI_CR1_DFF_8BIT        (0 << 11)
#define SPI_CR1_DFF_16BIT       (1 << 11)

/**@}*/

#define SPI_CR1_DFF         (1 << 11)
#define REMAP 1
#define NO_REMAP 0
void spi_reset(SPI_TypeDef *SPI);
int spi_init_master(SPI_TypeDef *SPI, uint32_t br, uint32_t cpol, uint32_t cpha,
		    uint32_t dff, uint32_t lsbfirst,uint8_t remap);
void spi_enable(SPI_TypeDef *SPI);
void spi_disable(SPI_TypeDef *SPI);
uint16_t spi_clean_disable(SPI_TypeDef *SPI);
void spi_write(SPI_TypeDef *SPI, uint16_t data);
void spi_send(SPI_TypeDef *SPI, uint8_t data);
uint16_t spi_read(SPI_TypeDef *SPI);
uint16_t spi_xfer(SPI_TypeDef *SPI, uint16_t data);
void spi_set_bidirectional_mode(SPI_TypeDef *SPI);
void spi_set_unidirectional_mode(SPI_TypeDef *SPI);
void spi_set_bidirectional_receive_only_mode(SPI_TypeDef *SPI);
void spi_set_bidirectional_transmit_only_mode(SPI_TypeDef *SPI);
void spi_enable_crc(SPI_TypeDef *SPI);
void spi_disable_crc(SPI_TypeDef *SPI);
void spi_set_next_tx_from_buffer(SPI_TypeDef *SPI);
void spi_set_next_tx_from_crc(SPI_TypeDef *SPI);
void spi_set_dff_8bit(SPI_TypeDef *SPI);
void spi_set_dff_16bit(SPI_TypeDef *SPI);
void spi_set_full_duplex_mode(SPI_TypeDef *SPI);
void spi_set_receive_only_mode(SPI_TypeDef *SPI);
void spi_disable_software_slave_management(SPI_TypeDef *SPI);
void spi_enable_software_slave_management(SPI_TypeDef *SPI);
void spi_set_nss_high(SPI_TypeDef *SPI);
void spi_set_nss_low(SPI_TypeDef *SPI);
void spi_send_lsb_first(SPI_TypeDef *SPI);
void spi_send_msb_first(SPI_TypeDef *SPI);
void spi_set_baudrate_prescaler(SPI_TypeDef *SPI, uint8_t baudrate);
void spi_set_master_mode(SPI_TypeDef *SPI);
void spi_set_slave_mode(SPI_TypeDef *SPI);
void spi_set_clock_polarity_1(SPI_TypeDef *SPI);
void spi_set_clock_polarity_0(SPI_TypeDef *SPI);
void spi_set_clock_phase_1(SPI_TypeDef *SPI);
void spi_set_clock_phase_0(SPI_TypeDef *SPI);
void spi_enable_tx_buffer_empty_interrupt(SPI_TypeDef *SPI);
void spi_disable_tx_buffer_empty_interrupt(SPI_TypeDef *SPI);
void spi_enable_rx_buffer_not_empty_interrupt(SPI_TypeDef *SPI);
void spi_disable_rx_buffer_not_empty_interrupt(SPI_TypeDef *SPI);
void spi_enable_error_interrupt(SPI_TypeDef *SPI);
void spi_disable_error_interrupt(SPI_TypeDef *SPI);
void spi_enable_ss_output(SPI_TypeDef *SPI);
void spi_disable_ss_output(SPI_TypeDef *SPI);
void spi_enable_tx_dma(SPI_TypeDef *SPI);
void spi_disable_tx_dma(SPI_TypeDef *SPI);
void spi_enable_rx_dma(SPI_TypeDef *SPI);
void spi_disable_rx_dma(SPI_TypeDef *SPI);
void spi_set_standard_mode(SPI_TypeDef *SPI, uint8_t mode);
int spi_dma_transceive(uint8_t *tx_buf, int tx_len, uint8_t *rx_buf, int rx_len);
int spi2_dma_transceive(uint8_t *tx_buf, int tx_len, uint8_t *rx_buf, int rx_len);
void spi1_dma_receive(uint8_t *rx_buf, int rx_len);
void spi1_dma_transmit(uint8_t *tx_buf, int tx_len);

#endif
