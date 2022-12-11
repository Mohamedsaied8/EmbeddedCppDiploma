/* USART SETUP STEPS:
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take place.
Configure the DMA register as explained in multibuffer communication. 
5.Select the desired baud rate using the baud rate register USART_BRR
6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit.
*/
	
/** @brief USART source file.

This source file should include functions to do the following 
@USART Initialize
@USART Read Character
@USART Write Character
@USART Write String
*/

/*---------------------------------------------------------------------------*/
/** @brief USART initialization.

This initialize the GPIO enables it's clock
*Specify the mode of TX & RX pins as Alt. Push-Pull and IN Floating
*Baud Rate Divisor
*Enable USART Clock Gating
*Enable  USART | Enable Tx & Rx Functionality
*Enable/Disable DMA Functionality

@param[in] USARTx. i.e USART1  @ref

@param[in] 16-bits value specify the desired Baud Rate.

*/
#include "usart.h"
#include "dma.h"


// double rate,Div;
extern int __clk;

/*
void usartremap(USART_TypeDef *usart, int setmap){
	if(usart==USART1){
    AFIO->MAPR   &= ~(1<<2);         // reset USART1 remap 
		if(setmap==1)   AFIO->MAPR   |= 1<<2;            //   set USART1 remap, PA9 -> PB6 , PA10 -> PB7	
	}
	else if(usart==USART2){
	 	AFIO->MAPR   &= ~(1<<3);     // reset USART2 remap
  	if(setmap==1)   AFIO->MAPR   |= 1<<3;        //   set USART2 remap, PA2 -> PD5 , PA3 -> PD6		
	}
}
*/
void usartInit(USART_TypeDef *usart,uint32_t br, int setremap){
	if(usart==USART1){
		  // make sure the relevant pins are appropriately set up.
  	 if(setremap==0)                 {
	  RCC->APB2ENR |= 1<<2;											  	// enable clock for GPIOA		
    GPIOA->CRH   |= (0x0BUL  << 4);                  // Tx (PA9) alt. out push-pull
    GPIOA->CRH   |= (0x04UL  << 8);  }                // Rx (PA10) in floating
	  if(setremap==1)                  {	
	  RCC->APB2ENR |= 1<<3;	
		RCC->APB2ENR |= 0x01;            // enable clock for Alternate Function FOR REMAP// enable clock for GPIOD				
		AFIO->MAPR   &= ~(1<<2); 			
		AFIO->MAPR   |= 1<<2;          //   set USART1 remap	
		GPIOB->CRL   |= (0x0BUL  << 24);            // Tx (PB6) alt. out push-pull
    GPIOB->CRL   |= (0x04UL  << 28); }           // RX  (PB7)
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;            // enable clock for USART1
		
	}
	else if(usart==USART2){
	  if(setremap==0)                    {
	  RCC->APB2ENR |= 1<<2;												  	// enable clock for GPIOA				
		GPIOA->CRL   |= (0x0BUL  << 8);                  // Tx (PA2) alt. out push-pull
    GPIOA->CRL   |= (0x04UL  << 12);	 }              // RX  (PA3)	
	  if(setremap==1)                  {	
	  RCC->APB2ENR |= 1<<5;	                          // enable clock for GPIOD
		RCC->APB2ENR |= 0x01;            // enable clock for Alternate Function FOR REMAP// enable clock for GPIOD				
		AFIO->MAPR   &= ~(1<<3); 			
		AFIO->MAPR   |= 1<<3;          //   set USART2 remap	
		GPIOD->CRL   |= (0x0BUL  << 20);            // Tx (PD5) alt. out push-pull
    GPIOD->CRL   |= (0x04UL  << 24); }           // RX  (PD6)
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;		
	}
	else if(usart==USART3){
    RCC->APB2ENR |= 1<<3;													  // enable clock for GPIOB
	GPIOB->CRH   |= (0x0BUL  << 8);                   // Tx (PB10) alt. out push-pull
    GPIOB->CRH   |= (0x04UL  << 12);                  // Rx (PB11) in floating
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	
	}
	else if(usart==USART4){
	RCC->APB2ENR |= 1<<4;												   	// enable clock for GPIOB
	GPIOC->CRH   |= (0x0BUL  << 8);                   // Tx (PB10) alt. out push-pull
    GPIOC->CRH   |= (0x04UL  << 12);
	RCC->APB1ENR |= RCC_APB1ENR_USART4EN;		
	}
	else if(usart==USART5){
		
	RCC->APB2ENR |= 1<<4;															// enable clock for GPIOC
	RCC->APB2ENR |= 1<<5;															// enable clock for GPIOD
	GPIOC->CRH   |= (0x0BUL  << 14);                  // Tx (PC12) alt. out push-pull
    GPIOD->CRH   |= (0x04UL  << 8); 									// Rx (PD2) in floating
	RCC->APB1ENR |= RCC_APB1ENR_USART5EN;		
	}
//    Div= ((__clk) / (16 * (br/pow(1000,2))));
//	rate=Div*16;   // fraction

    usart->BRR   = __clk*1000000/br;		// set baudrate
//	usart->CR1 =1<<12;   // for 9 bit
    usart->CR1  |= (USART_CR1_RE | USART_CR1_TE);  // RX, TX enable
    usart->CR1  |= USART_CR1_UE;                    // USART enable/
	  usart->CR3 |= USART_DMA_EN;
	
	
}

/** @brief     Send character.
		@param[in] *uart i.e USART1
		@param[in] ch i.e 'a'
		@example  sendChar(USART1,'a');
*/
void sendChar(USART_TypeDef *uart,char ch){
  while (!(uart->SR & USART_SR_TXE));
  uart->DR = (ch & 0xFF);
  
}

/** @brief     Recieve character.
		@param[in] *uart i.e USART1
		@param[out] urt->DR i.e USASRT1->DR; \f
								return value of the incoming character
		@example  char _recieve=GetChar(USART1);
*/
unsigned char GetChar (USART_TypeDef *urt)  {
  while (!(urt->SR & USART_SR_RXNE));
  return ((unsigned char)(urt->DR & 0xFF));
}
/** @brief Send String aka Array of Characters.
		@param[in] *uart i.e USART1
		@param[in] *str i.e char *device="Mcu";
		@example   Send_String(USART1,device); and or \or
               Send_String(USART1,"hello Mcu"); 
*/
void Send_String(USART_TypeDef *uart,char *str)
 {
    volatile int __i = 0;

    while(str[__i] != 0) {
        sendChar(uart,str[__i++]);
    }
}		
	

/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART1.
        @param[in] *data i.e char *device="Hello Mcu";
        @example   dma_write_usart1(device,10); and or \or
                   dma_write_usart1("hello Mcu",10);
*/
void dma_write_usart1(char *data, int size)
{
    /*
     * Using channel 4 for USART1_TX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL4);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL4, (u32)&USART1->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL4, (u32)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL4, size);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL4);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL4);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL4, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL4, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL4, DMA_CCR_PL_VERY_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);

    dma_enable_channel(DMA1, DMA_CHANNEL4);

      //  usart_enable_tx_dma(USART2);
                USART1->CR3 |= USART_DMA_EN;
}
/** @brief Read String aka Array of Characters Using Direct Memory Access Channel for USART1.
        @param[in] *data i.e char *device="Hello Mcu";
        @example   dma_write_usart1(device,10); and or \or
                   dma_write_usart1("hello Mcu",10);
*/
void dma_read_usart1(char *data, int size)
{
    /*
     * Using channel 5 for USART1_RX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL5);

   dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t)&USART1->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL5, size);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL5);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);

    dma_enable_channel(DMA1, DMA_CHANNEL5);

       // usart_enable_rx_dma(USART2);
             USART1->CR3 |= 1<<6;
}

/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART2.
        @param[in] *data i.e char *device="Hello Mcu";
        @example   dma_write_usart2(device,10); and or \or
                   dma_write_usart2("hello Mcu",10);
*/
void dma_write_usart2(char *data, int size)
{
    /*
     * Using channel 7 for USART2_TX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL7);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL7, (u32)&USART2->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL7, (u32)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL7, size);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL7);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL7);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL7, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL7, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL7, DMA_CCR_PL_VERY_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL7);

    dma_enable_channel(DMA1, DMA_CHANNEL7);

      //  usart_enable_tx_dma(USART2);
                USART2->CR3 |= USART_DMA_EN;
}
/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART2.
        @param[in] *data Expected recieved Array of characters i.e char device[size];
        @param[in] size Number of expected recieved Array of characters i.e size  10
        @example   dma_read_usart4(device,10);
*/
void dma_read_usart2(char *data, int size)
{
    /*
     * Using channel 6 for USART2_RX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL6);

   dma_set_peripheral_address(DMA1, DMA_CHANNEL6, (uint32_t)&USART2->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL6, (uint32_t)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL6, size);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL6);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL6);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL6, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL6, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL6, DMA_CCR_PL_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL6);

    dma_enable_channel(DMA1, DMA_CHANNEL6);

       // usart_enable_rx_dma(USART2);
             USART2->CR3 |= 1<<6;
}
/*---------USART3 DMA-----------------*/
/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART3.
        @param[in] *data i.e char *device="Hello Mcu";
        @example   dma_write_usart3(device,10); and or \or
                   dma_write_usart3("hello Mcu",10);
*/
void dma_write_usart3(char *data, int size)
{
    /*
     * Using channel 2 for USART3_TX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL7);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL2, (u32)&USART3->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL2, (u32)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL2, size);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL2);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL2);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL2, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL2, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL2, DMA_CCR_PL_VERY_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL2);

    dma_enable_channel(DMA1, DMA_CHANNEL2);

      //  usart_enable_tx_dma(USART2);
                USART3->CR3 |= USART_DMA_EN;
}
/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART3.
        @param[in] *data Expected recieved Array of characters i.e char device[size];
        @param[in] size Number of expected recieved Array of characters i.e size  10
        @example   dma_read_usart3(device,10);
*/
void dma_read_usart3(char *data, int size)
{
    /*
     * Using channel 3 for USART3_RX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA1, DMA_CHANNEL3);

   dma_set_peripheral_address(DMA1, DMA_CHANNEL3, (uint32_t)&USART3->DR);
    dma_set_memory_address(DMA1, DMA_CHANNEL3, (uint32_t)data);
    dma_set_number_of_data(DMA1, DMA_CHANNEL3, size);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL3);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL3);
    dma_set_peripheral_size(DMA1, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_CHANNEL3, DMA_CCR_PL_HIGH);

    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL3);

    dma_enable_channel(DMA1, DMA_CHANNEL3);

       // usart_enable_rx_dma(USART2);
             USART3->CR3 |= 1<<6;
}

/*----------DMA USART4-----------------*/
/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART4.
        @param[in] *data i.e char *device="Hello Mcu";
        @example   dma_write_usart4(device,10); and or \or
                   dma_write_usart4("hello Mcu",10);
*/
void dma_write_usart4(char *data, int size)
{
    /*
     * Using channel 5 for USART4_TX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA2, DMA_CHANNEL5);

    dma_set_peripheral_address(DMA2, DMA_CHANNEL5, (u32)&USART4->DR);
    dma_set_memory_address(DMA2, DMA_CHANNEL5, (u32)data);
    dma_set_number_of_data(DMA2, DMA_CHANNEL5, size);
    dma_set_read_from_memory(DMA2, DMA_CHANNEL5);
    dma_enable_memory_increment_mode(DMA2, DMA_CHANNEL5);
    dma_set_peripheral_size(DMA2, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA2, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA2, DMA_CHANNEL5, DMA_CCR_PL_VERY_HIGH);

    dma_enable_transfer_complete_interrupt(DMA2, DMA_CHANNEL5);

    dma_enable_channel(DMA2, DMA_CHANNEL5);

      //  usart_enable_tx_dma(USART2);
                USART4->CR3 |= USART_DMA_EN;
}
/** @brief Send String aka Array of Characters Using Direct Memory Access Channel for USART4.
        @param[in] *data Expected recieved Array of characters i.e char device[size];
        @param[in] size Number of expected recieved Array of characters i.e size  10
        @example   dma_read_usart4(device,10);
*/
void dma_read_usart4(char *data, int size)
{
    /*
     * Using channel 3 for USART4_RX
     */

    /* Reset DMA channel*/
    dma_channel_reset(DMA2, DMA_CHANNEL3);

   dma_set_peripheral_address(DMA2, DMA_CHANNEL3, (uint32_t)&USART4->DR);
    dma_set_memory_address(DMA2, DMA_CHANNEL3, (uint32_t)data);
    dma_set_number_of_data(DMA2, DMA_CHANNEL3, size);
    dma_set_read_from_peripheral(DMA2, DMA_CHANNEL3);
    dma_enable_memory_increment_mode(DMA2, DMA_CHANNEL3);
    dma_set_peripheral_size(DMA2, DMA_CHANNEL3, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA2, DMA_CHANNEL3, DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA2, DMA_CHANNEL3, DMA_CCR_PL_HIGH);

    dma_enable_transfer_complete_interrupt(DMA2, DMA_CHANNEL3);

    dma_enable_channel(DMA2, DMA_CHANNEL3);

       // usart_enable_rx_dma(USART2);
             USART4->CR3 |= 1<<6;
}





