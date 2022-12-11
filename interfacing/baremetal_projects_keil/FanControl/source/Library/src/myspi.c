#include "spi.h"

/** @brief Configure the SPI as Master.
The SPI peripheral is configured as a master with communication parameters
baudrate, data format 8/16 bits, frame format lsb/msb first, clock polarity
and phase. The SPI enable, CRC enable and CRC next controls are not affected.
These must be controlled separately.
To support multiple masters (dynamic switching between master and slave)
you must set SSOE to 0 and select either software or hardware control of
the NSS pin.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
@param[in] br Unsigned int32. Baudrate @ref spi_baudrate.
@param[in] cpol Unsigned int32. Clock polarity @ref spi_cpol.
@param[in] cpha Unsigned int32. Clock Phase @ref spi_cpha.
@param[in] dff Unsigned int32. Data frame format 8/16 bits @ref spi_dff.
@param[in] lsbfirst Unsigned int32. Frame format lsb/msb first @ref
spi_lsbfirst.
@returns int. Error code.
*/
typedef enum {
	NONE = 0,
	ONE,
	DONE
} trans_status;
volatile trans_status transceive_status;

int spi_init_master(SPI_TypeDef *SPI, uint32_t br, uint32_t cpol, uint32_t cpha,
		    uint32_t dff, uint32_t lsbfirst,uint8_t remap)
{	
	uint32_t reg32 = SPI->CR1;
	
	if(remap!=0){
		
 
 if(SPI==SPI1){
	RCC->APB2ENR |=1;					//Enable Alternate Function
	AFIO->MAPR |= 1<<0; 			// remap SPI1	
	RCC->APB2ENR|=(1<<3);			//Enable GPIOB CLOCK
	RCC->APB1ENR|=(1<<14);		//Enable SPI CLOCK
	portInit(GPIOB,!(1<<4));
  portInitAlt(GPIOB,0x0028);
	}	
	else if(SPI==SPI3){	
  RCC->APB2ENR |= 1; // enable clock for AF
	AFIO->MAPR |= 1<<28; // remap SPI3
	RCC->APB2ENR |= 1<<4; // enable clock for GPIOC
	RCC->APB1ENR |= 1<<15; // enable clock for SPI3
	// SPI3_SCK, SPI3_MISO, SPI3_MOSI are SPI pins		
  portInitAlt(GPIOC,0x1400);
	GPIOC->CRH |=(8<<12);
	portInit(GPIOE,0x0002);		
	}
}
	
else{	
if(SPI==SPI1){	
	RCC->APB2ENR |=1;					//Enable Alternate Function
	RCC->APB2ENR|=(1<<2);			//Enable GPIOA CLOCK
	RCC->APB2ENR|=(1<<12);		//Enable SPI1 CLOCK
	portInitAlt(GPIOA,0x00A0);
	GPIOA->CRL|=(8<<24);
}
else if(SPI==SPI2){	
	RCC->APB2ENR |=1;					//Enable Alternate Function
	RCC->APB2ENR|=(1<<3);			//Enable GPIOB CLOCK
	RCC->APB1ENR|=(1<<14);		//Enable SPI2 CLOCK
	GPIOA->CRH&=0xFFF00000;
	GPIOA->CRH|=0xB4B00000;
 //	portInitAlt(GPIOA,0x00A0);
}

	}

	/* Reset all bits omitting SPE, CRCEN and CRCNEXT bits. */
	reg32 &= SPI_CR1_SPE | SPI_CR1_CRCEN | SPI_CR1_CRCNEXT;


	reg32 |= br;		/* Set baud rate bits. */
	reg32 |= cpol;		/* Set CPOL value. */
	reg32 |= cpha;		/* Set CPHA value. */
	reg32 |= dff;		/* Set data format (8 or 16 bits). */
	reg32 |= lsbfirst;	/* Set frame format (LSB- or MSB-first). */
	reg32 |= SPI_CR1_MSTR;	/* Configure SPI as master. */
	//reg32 |=SPI_CR1_SPE;
	 //SPI->CR2 |= SPI_CR2_SSOE; /* common case */
	 SPI->CR1 |= reg32;
	
	return 0; /* TODO */
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Set Data Frame Format to 8 bits
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_set_dff_8bit(SPI_TypeDef *SPI)
{
	SPI->CR1  &= ~SPI_CR1_DFF;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Set Data Frame Format to 16 bits
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_set_dff_16bit(SPI_TypeDef *SPI)
{
	SPI->CR1|= SPI_CR1_DFF;
}

void spi_write(SPI_TypeDef *SPI, uint16_t data)
{
	/* Write data (8 or 16 bits, depending on DFF) into DR. */
	SPI->DR = data;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Data Write with Blocking.
Data is written to the SPI interface after the previous write transfer has
finished.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
@param[in] data Unsigned int16. 8 or 16 bit data to be written.
*/

void spi_send(SPI_TypeDef *SPI, uint8_t data)
{
	/* Wait for transfer finished. */
	while (!(SPI->SR  & SPI_SR_TXE));

	/* Write data (8 or 16 bits, depending on DFF) into DR. */
	SPI->DR  = data;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Data Read.
Data is read from the SPI interface after the incoming transfer has finished.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
@returns data Unsigned int16. 8 or 16 bit data.
*/

uint16_t spi_read(SPI_TypeDef *SPI)
{
	/* Wait for transfer finished. */
	while (!(SPI->SR & SPI_SR_RXNE));

	/* Read the data (8 or 16 bits, depending on DFF bit) from DR. */
	return SPI->DR;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Data Write and Read Exchange.
Data is written to the SPI interface, then a read is done after the incoming
transfer has finished.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
@param[in] data Unsigned int16. 8 or 16 bit data to be written.
@returns data Unsigned int16. 8 or 16 bit data.
*/

uint16_t spi_xfer(SPI_TypeDef *SPI, uint16_t data)
{
	spi_write(SPI, data);

	/* Wait for transfer finished. */
	while (!(SPI->SR & SPI_SR_RXNE));

	/* Read the data (8 or 16 bits, depending on DFF bit) from DR. */
	return SPI->DR;
}
void spi_enable_crc(SPI_TypeDef *SPI)
{
	SPI->CR1  |= SPI_CR1_CRCEN;
}
void spi_disable_crc(SPI_TypeDef *SPI)
{
	SPI->CR1  &= ~SPI_CR1_CRCEN;
}
/** @brief SPI Disable Slave Management by Hardware
In slave mode the NSS hardware input is used as a select enable for the slave.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_disable_software_slave_management(SPI_TypeDef *SPI)
{
	SPI->CR1  &= ~SPI_CR1_SSM;
}
/** @brief SPI Enable Slave Management by Software
In slave mode the NSS hardware input is replaced by an internal software
enable/disable of the slave (@ref spi_set_nss_high).
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_enable_software_slave_management(SPI_TypeDef *SPI)
{
	SPI->CR1 |= SPI_CR1_SSM;
	/* allow slave select to be an input */
	SPI->CR2&= ~SPI_CR2_SSOE;
}
/** @brief SPI Set the Software NSS Signal High
In slave mode, and only when software slave management is used, this replaces
the NSS signal with a slave select enable signal.
@todo these should perhaps be combined with an SSM enable as it is meaningless
otherwise
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_set_nss_high(SPI_TypeDef *SPI)
{
	SPI->CR1|= SPI_CR1_SSI;
}
/** @brief SPI Enable Transmit Transfers via DMA
This allows transmissions to proceed unattended using DMA to move data to the
transmit buffer as it becomes available. The DMA channels provided for each
SPI peripheral are given in the Technical Manual DMA section.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_enable_tx_dma(SPI_TypeDef *SPI)
{
	SPI->CR2 |= SPI_CR2_TXDMAEN;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Disable Transmit Transfers via DMA
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_disable_tx_dma(SPI_TypeDef *SPI)
{
	SPI->CR2 &= ~SPI_CR2_TXDMAEN;
}
/** @brief SPI Enable Receive Transfers via DMA
This allows received data streams to proceed unattended using DMA to move data
from the receive buffer as data becomes available. The DMA channels provided
for each SPI peripheral are given in the Technical Manual DMA section.
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_enable_rx_dma(SPI_TypeDef *SPI)
{
	SPI->CR2  |= SPI_CR2_RXDMAEN;
}

/*---------------------------------------------------------------------------*/
/** @brief SPI Disable Receive Transfers via DMA
@param[in] spi Unsigned int32. SPI peripheral identifier @ref spi_reg_base.
*/

void spi_disable_rx_dma(SPI_TypeDef *SPI)
{
	SPI->CR2 &= ~SPI_CR2_RXDMAEN;
}

void spi_enable(SPI_TypeDef *SPI)
{
	SPI->CR1 |= SPI_CR1_SPE; /* Enable SPI. */
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													
}
void spi_set_nss_low(SPI_TypeDef *SPI)
{
	SPI->CR1 &= ~SPI_CR1_SSI;
}

void spi_reset(SPI_TypeDef *SPI){
	
	RCC->APB2RSTR=1<<12;
}
uint16_t spi_clean_disable(SPI_TypeDef *SPI)
{uint16_t data;
	/* Wait to receive last data */
	while (!(SPI->SR  & SPI_SR_RXNE));

	data = SPI->DR;

	/* Wait to transmit last data */
	while (!(SPI->SR & SPI_SR_TXE));

	/* Wait until not busy */
	while (SPI->SR & SPI_SR_BSY);

	SPI->CR1 &= ~SPI_CR1_SPE;

	return data;
}
void spi_set_next_tx_from_buffer(SPI_TypeDef *SPI)
{
	SPI->CR1 &= ~SPI_CR1_CRCNEXT;
}

void spi_enable_ss_output(SPI_TypeDef *SPI)
{
	SPI->CR2 |= SPI_CR2_SSOE;
}

/* SPI transmit completed with DMA */
void DMAChannel3_IRQHandler(void)
{
	 
	if ((DMA1_ISR &DMA_ISR_TCIF3) != 0) {
		DMA1_IFCR |= DMA_IFCR_CTCIF3;
	}

	dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL3);

	 spi_disable_tx_dma(SPI1);

	dma_disable_channel(DMA1, DMA_CHANNEL3);
   
	//transceive_status++;
}
/* SPI2 transmit completed with DMA */
void DMAChannel5_IRQHandler(void)
{
	 
	if ((DMA1_ISR &DMA_ISR_TCIF5) != 0) {
		DMA1_IFCR |= DMA_IFCR_CTCIF5;
	}

	dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);

	 spi_disable_tx_dma(SPI2);

	dma_disable_channel(DMA1, DMA_CHANNEL5);
   
	//transceive_status++;
}
/* SPI receive completed with DMA */
void DMAChannel2_IRQHandler(void)
{ 
	if ((DMA1_ISR &DMA_ISR_TCIF2) != 0) {
		DMA1_IFCR |= DMA_IFCR_CTCIF2;
	}

	dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);

	 spi_disable_rx_dma(SPI1);

	dma_disable_channel(DMA1, DMA_CHANNEL2);
// transceive_status++;
}

/* SPI3 receive completed with DMA */
void DMAChannel4_IRQHandler(void)
{ 
	if ((DMA1_ISR &DMA_ISR_TCIF4) != 0) {
		DMA1_IFCR |= DMA_IFCR_CTCIF4;
	}

	dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);

	 spi_disable_rx_dma(SPI2);

	dma_disable_channel(DMA1, DMA_CHANNEL4);
 
}

void spi1_dma_transmit(uint8_t *tx_buf, int tx_len){
		volatile uint8_t temp_data;
	dma_channel_reset(DMA1, DMA_CHANNEL3);

	/* Reset SPI data and status registers.
	 * Here we assume that the SPI peripheral is NOT
	 * busy any longer, i.e. the last activity was verified
	 * complete elsewhere in the program.
	 */
/*
 	while (SPI1->SR  & (SPI_SR_RXNE | SPI_SR_OVR)) {
		temp_data = SPI1->DR ;
	} 
	*/
	transceive_status = ONE;
	/* Set up tx dma */
	if (tx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL3, (uint32_t)&SPI1->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL3, (uint32_t)tx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL3, tx_len);
		dma_set_read_from_memory(DMA1, DMA_CHANNEL3);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL3, DMA_CCR_PL_LOW);	
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL3);
		dma_enable_channel(DMA1, DMA_CHANNEL3);
		spi_enable_tx_dma(SPI1);
		
	}
		 while (!(SPI1->SR & SPI_SR_TXE)); // Wait for bus free
			while (SPI1->SR  & SPI_SR_BSY);
	
}
void spi1_dma_receive(uint8_t *rx_buf, int rx_len){
		volatile uint8_t temp_data;
	dma_channel_reset(DMA1, DMA_CHANNEL2);

	/* Reset SPI data and status registers.
	 * Here we assume that the SPI peripheral is NOT
	 * busy any longer, i.e. the last activity was verified
	 * complete elsewhere in the program.
	 */
 /*
 	while (SPI1->SR  & (SPI_SR_RXNE | SPI_SR_OVR)) {
		temp_data = SPI1->DR ;
	}  
	*/
	//transceive_status = ONE;
	/* Set up tx dma */
 	
	/* Set up rx dma, note it has higher priority to avoid overrun */
	  if (rx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL2, (uint32_t)&SPI1->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL2, (uint32_t)rx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL2, rx_len);
		dma_set_read_from_peripheral(DMA1, DMA_CHANNEL2);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL2);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL2, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL2, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL2, DMA_CCR_PL_HIGH);
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);
		dma_enable_channel(DMA1, DMA_CHANNEL2);
		spi_enable_rx_dma(SPI1);
	} 
 	while (!(SPI1->SR & SPI_SR_TXE));
		//BSY=0
	
}
	
int spi_dma_transceive(uint8_t *tx_buf, int tx_len, uint8_t *rx_buf, int rx_len)
 
{		volatile uint8_t temp_data;
	/* Check for 0 length in both tx and rx */
	/*if ((rx_len < 1) && (tx_len < 1)) {
		 return -1 as error */
		/*return -1;
	}
*/
	/* Reset DMA channels*/
	dma_channel_reset(DMA1, DMA_CHANNEL3);
	dma_channel_reset(DMA1, DMA_CHANNEL2);

	/* Reset SPI data and status registers.
	 * Here we assume that the SPI peripheral is NOT
	 * busy any longer, i.e. the last activity was verified
	 * complete elsewhere in the program.
	 */
	
 	while (SPI1->SR  & (SPI_SR_RXNE | SPI_SR_OVR)) {
		temp_data = SPI1->DR ;
	} 
	
	/* Set up rx dma, note it has higher priority to avoid overrun */
	  if (rx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL2, (uint32_t)&SPI1->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL2, (uint32_t)rx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL2, rx_len);
		dma_set_read_from_peripheral(DMA1, DMA_CHANNEL2);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL2);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL2, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL2, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL2, DMA_CCR_PL_VERY_HIGH);
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);
		dma_enable_channel(DMA1, DMA_CHANNEL2);
		spi_enable_rx_dma(SPI1);
	} 
 
transceive_status = ONE;
	/* Set up tx dma */
	if (tx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL3, (uint32_t)&SPI1->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL3, (uint32_t)tx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL3, tx_len);
		dma_set_read_from_memory(DMA1, DMA_CHANNEL3);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL3, DMA_CCR_PL_HIGH);	
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL3);
		dma_enable_channel(DMA1, DMA_CHANNEL3);
		spi_enable_tx_dma(SPI1);
	}
	 while (!(SPI1->SR & SPI_SR_TXE)); // Wait for bus free
 	  while (SPI1->SR  & SPI_SR_BSY);
	
 	return 0;
	 
}
//spi2
	
int spi2_dma_transceive(uint8_t *tx_buf, int tx_len, uint8_t *rx_buf, int rx_len)
 
{		volatile uint8_t temp_data;
	/* Check for 0 length in both tx and rx */
	/*if ((rx_len < 1) && (tx_len < 1)) {
		 return -1 as error */
		/*return -1;
	}
*/
	/* Reset DMA channels*/
	dma_channel_reset(DMA1, DMA_CHANNEL4);
	dma_channel_reset(DMA1, DMA_CHANNEL5);

	/* Reset SPI data and status registers.
	 * Here we assume that the SPI peripheral is NOT
	 * busy any longer, i.e. the last activity was verified
	 * complete elsewhere in the program.
	 */
	
 	while (SPI2->SR  & (SPI_SR_RXNE | SPI_SR_OVR)) {
		temp_data = SPI1->DR ;
	} 
	/* Set up rx dma, note it has higher priority to avoid overrun */
	  if (rx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL4, (uint32_t)&SPI2->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL4, (uint32_t)rx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL4, rx_len);
		dma_set_read_from_peripheral(DMA1, DMA_CHANNEL4);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL4);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL4, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL4, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL4, DMA_CCR_PL_VERY_HIGH);
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);
		dma_enable_channel(DMA1, DMA_CHANNEL4);
		spi_enable_rx_dma(SPI2);
	} 
 
transceive_status = ONE;
	/* Set up tx dma */
	if (tx_len > 0) {
		dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)&SPI2->DR);
		dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)tx_buf);
		dma_set_number_of_data(DMA1, DMA_CHANNEL5, tx_len);
		dma_set_read_from_memory(DMA1, DMA_CHANNEL5);
		dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
		dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
		dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
		dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_HIGH);	
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);
		dma_enable_channel(DMA1, DMA_CHANNEL5);
		spi_enable_tx_dma(SPI2);
	}
	/* if(PINA&0x0020==0)
	{ // for 100 ms then an error happened
   return -1;
	}
	else*/ return 0;
	 
}
