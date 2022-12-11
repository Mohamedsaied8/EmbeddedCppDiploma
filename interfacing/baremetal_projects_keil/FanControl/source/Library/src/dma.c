#include "dma.h"

/** @brief Reset The desired DMA Channel.
		@param[in] DMA i.e DMA1
		@param[in] DMA channel i.e DMA_CHANNEL1
		@example   dma_channel_reset(DMA1,DMA_CHANNEL1);
*/
void dma_channel_reset(u32 dma, u8 channel)
{
	/* Disable channel. */
	DMA_CCR(dma, channel) &= ~DMA_CCR_EN;
	/* Reset config bits. */
	DMA_CCR(dma, channel) = 0;
	/* Reset data transfer number. */
	DMA_CNDTR(dma, channel) = 0;
	/* Reset peripheral address. */
	DMA_CPAR(dma, channel) = 0;
	/* Reset memory address. */
	DMA_CMAR(dma, channel) = 0;
	/* Reset interrupt flags. */
	DMA_IFCR(dma) |= DMA_IFCR_CIF(channel);
}
/** @brief Enable Memory To Memory Transfer Mode.
		@param[in] DMA i.e DMA1
		@param[in] DMA channel i.e DMA_CHANNEL1
		@example   dma_enable_mem2mem_mode(DMA1,DMA_CHANNEL1);
*/
void dma_enable_mem2mem_mode(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_MEM2MEM;
	DMA_CCR(dma, channel) &= ~DMA_CCR_CIRC;
}
/** @brief Set Priority for the DMA channel Transfer.
		@param[in] DMA i.e DMA1
		@param[in] DMA channel i.e DMA_CHANNEL1
		@param[in] DMA channel Priority i.e DMA_CCR_PL_VERY_HIGH
		@example   dma_set_priority(DMA1,DMA_CHANNEL1,DMA_CCR_PL_VERY_HIGH);
*/
void dma_set_priority(u32 dma, u8 channel, u32 prio)
{
	DMA_CCR(dma, channel) &= ~(DMA_CCR_PL_MASK);
	DMA_CCR(dma, channel) |= prio;
}
/** @brief Set Priority for the DMA channel Transfer.
		@param[in] DMA i.e DMA1
		@param[in] DMA channel i.e DMA_CHANNEL1
		@param[in] DMA channel size i.e DMA_CCR_MSIZE_8BIT
		@example   dma_set_memory_size(DMA1,DMA_CHANNEL1,DMA_CCR_MSIZE_8BIT);
*/
void dma_set_memory_size(u32 dma, u8 channel, u32 mem_size)
{

	DMA_CCR(dma, channel) &= ~(DMA_CCR_MSIZE_MASK);
	DMA_CCR(dma, channel) |= mem_size;
}
/** @brief Set Priority for the DMA channel Transfer.
		@param[in] DMA i.e DMA1
		@param[in] DMA channel i.e DMA_CHANNEL1
		@param[in] DMA channel size i.e DMA_CCR_MSIZE_8BIT
		@example   dma_set_memory_size(DMA1,DMA_CHANNEL1,DMA_CCR_MSIZE_8BIT);
*/
void dma_set_peripheral_size(u32 dma, u8 channel, u32 peripheral_size)
{
	DMA_CCR(dma, channel) &= ~(DMA_CCR_PSIZE_MASK);
	DMA_CCR(dma, channel) |= peripheral_size;
}
/** @brief Enable memory increment for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_memory_increment_mode(DMA1,DMA_CHANNEL1);
*/
void dma_enable_memory_increment_mode(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_MINC;
}
/** @brief Enable Peripheral increment for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_peripheral_increment_mode(DMA1,DMA_CHANNEL1);
*/
void dma_enable_peripheral_increment_mode(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_PINC;
}
/** @brief Enable Circular mode for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_circular_mode(DMA1,DMA_CHANNEL1);
*/
void dma_enable_circular_mode(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_CIRC;
	DMA_CCR(dma, channel) &= ~DMA_CCR_MEM2MEM;
}
/** @brief Enable Read from Peripheral for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_set_read_from_peripheral(DMA1,DMA_CHANNEL1);
*/
void dma_set_read_from_peripheral(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) &= ~DMA_CCR_DIR;
}
/** @brief Enable Read from memory for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_set_read_from_memory(DMA1,DMA_CHANNEL1);
*/
void dma_set_read_from_memory(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_DIR;
}
/** @brief Enable Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_transfer_error_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_enable_transfer_error_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_TEIE;
}
/** @brief Disable Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_disable_transfer_error_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_disable_transfer_error_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) &= ~DMA_CCR_TEIE;
}
/** @brief Enable half Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_half_transfer_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_enable_half_transfer_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_HTIE;
}
/** @brief Disable half Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_disable_half_transfer_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_disable_half_transfer_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) &= ~DMA_CCR_HTIE;
}

/** @brief Enable Complete Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_enable_transfer_complete_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_TCIE;
}
/** @brief Disable Complete Transfer Interrupt for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_disable_transfer_complete_interrupt(DMA1,DMA_CHANNEL1);
*/
void dma_disable_transfer_complete_interrupt(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) &= ~DMA_CCR_TCIE;
}
/** @brief Enable DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_enable_channel(DMA1,DMA_CHANNEL1);
*/
void dma_enable_channel(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) |= DMA_CCR_EN;
}
/** @brief Disable DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @example   dma_disable_channel(DMA1,DMA_CHANNEL1);
*/
void dma_disable_channel(u32 dma, u8 channel)
{
	DMA_CCR(dma, channel) &= ~DMA_CCR_EN;
}
/** @brief Set Peripheral Address for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @param[in] address i.e USART->DR (USART Data Register)
        @example   dma_set_peripheral_address(DMA1,DMA_CHANNEL1,&USART->DR);
*/
void dma_set_peripheral_address(u32 dma, u8 channel, u32 address)
{
	DMA_CPAR(dma, channel) = (u32) address;
}
/** @brief Set Peripheral Address for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @param[in] address i.e data
        @example   dma_set_memory_address(DMA1,DMA_CHANNEL1,&data);
*/
void dma_set_memory_address(u32 dma, u8 channel, u32 address)
{
	DMA_CMAR(dma, channel) = (u32) address;
}
/** @brief Set Peripheral Address for the DMA channel.
        @param[in] DMA i.e DMA1
        @param[in] DMA channel i.e DMA_CHANNEL1
        @param[in] number i.e 8
        @example   dma_set_number_of_data(DMA1,DMA_CHANNEL1,number);
*/
void dma_set_number_of_data(u32 dma, u8 channel, u16 number)
{
	DMA_CNDTR(dma, channel) = number;
}

