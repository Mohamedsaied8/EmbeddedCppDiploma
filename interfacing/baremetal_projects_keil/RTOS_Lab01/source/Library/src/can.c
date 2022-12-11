#include "can.h"
CAN_msg  CAN_TxMsg, CAN_RxMsg;
/** @brief CAN initialization.

This initialize the CAN BUS enables it's clock
*Go for Initialization Mode
*Specify the  TX & RX pins as Alt. Push-Pull and IN Floating Also (Remapped)
*Baud Rate 
*Specify the mode (POLLING \OR INTERRUPT)
*Enable Overrun FIFO Functionality
*Go for Normal Mode

	@param[in] CANx. i.e CAN1  @ref
	@param[in] __mode to decide the mode (POLLING \OR INTERRUPT).
	@example     canInit(CAN1,INTERRUPT); 

*/

void canInit(CAN_TypeDef *CAN,int _mode )
{
	if(CAN==CAN1){
    RCC->APB1ENR |= 1<<25;	       // enable clock for CAN1
  	RCC->APB2ENR |= 0x01;            // enable clock for Alternate Function
  	RCC->APB2ENR |= 1<<5;           // enable clock for GPIO D
  
  	AFIO->MAPR   &= ~(3<<13);     // reset CAN remap
  	AFIO->MAPR   |= 3<<13;            //   set CAN remap, use PD0, PD1

	  GPIOD->CRL &= ~(0x0F<<0);
    GPIOD->CRL |=  (0x08<<0);          // CAN RX pin PD.0 input push pull   
  	GPIOD->CRL &= ~(0x0F<<4);
  	GPIOD->CRL |=  (0x0B<<4);         //TX pin PD.1 AF output push pull 
	}
	else if(CAN==CAN2){
		RCC->APB1ENR |= 1<<26;	       // enable clock for CAN2
  	RCC->APB2ENR |= 0x01;            // enable clock for Alternate Function
  	RCC->APB2ENR |= 1<<3;           // enable clock for GPIO B
  
  	AFIO->MAPR   &= ~(1<<22);     // reset CAN remap
  	AFIO->MAPR   |= 1<<22;            //   set CAN remap, use PD0, PD1

	  GPIOB->CRL &= ~(0x0F<<20);
    GPIOB->CRL |=  (0x08<<20);          // CAN RX pin PB.5 input push pull   
  	GPIOB->CRL &= ~(0x0F<<24);
  	GPIOB->CRL |=  (0x0B<<24);         //TX pin PB.6 AF output push pull 
		
	}
	  CAN->MCR = 1;                           	// init mode  	
    CAN->MCR =(1<<4);                     //no retransmission   
    CAN->IER = _mode;                       // FIFO 0 msg pending
		//CAN->IER =  1<<3; 
		CAN->MCR &=~(1<<3);											//overun fifo 
    CAN->BTR =  0x031C0009;    							//bit-timing   
    CAN->MCR &= ~1;                      // normal operating mode, reset INRQ
}	


void CAN_wrMsg (CAN_TypeDef *CAN,CAN_msg *msg,int mailIndex)  {
CAN->sTxMailBox[mailIndex].TIR  = (unsigned int)(msg->id << 3) | 4; 
if (msg->type == DATA_FRAME)   // DATA FRAME
   CAN->sTxMailBox[mailIndex].TIR &= ~(1<<1);
else     // REMOTE FRAME
CAN->sTxMailBox[mailIndex].TIR |= 1<<1;
CAN->sTxMailBox[mailIndex].TDLR = (((unsigned int)msg->data[3] << 24) | 
                            ((unsigned int)msg->data[2] << 16) |
                            ((unsigned int)msg->data[1] <<  8) | 
                            ((unsigned int)msg->data[0])        );
														
CAN->sTxMailBox[mailIndex].TDHR = (((unsigned int)msg->data[7] << 24) | 
                            ((unsigned int)msg->data[6] << 16) |
                            ((unsigned int)msg->data[5] <<  8) |
                            ((unsigned int)msg->data[4])        );
CAN->sTxMailBox[mailIndex].TDTR &= ~0xf; // Setup length
CAN->sTxMailBox[mailIndex].TDTR |=  (msg->len & 0xf);
CAN->sTxMailBox[mailIndex].TIR |=  1;                     // transmit message
}
/** @brief CAN Transmit.

Sends a dedicated Message
*Specify Message Transmitter i.e CAN1
*Specify Message ID 
*Specify ID Type (EXTENDED \OR STANDARD) 
*Specify Frame Type (DATA_FRAME \OR REMOTE_FRAME)
*Specify which Mailbox to send the Message
*Send Message

	@param[in] CANx. i.e CAN1  @ref
	@param[in] id Message ID 
	@param[in] ID Type (EXTENDED \OR STANDARD) 
	@param[in] Frame Type (DATA_FRAME \OR REMOTE_FRAME)
  @param[in] Mailbox to send the Message
	@example   canInit(CAN1,INTERRUPT); 

*/
void canTransmit(CAN_TypeDef *CAN,int id,char idtype,char ftype, unsigned char *m,int _mailIndex)
{  	int i; 
   	CAN_TxMsg.id = id;     // initialise message to send
  	for (i = 0; i < 8; i++) CAN_TxMsg.data[i] = m[i];
  	CAN_TxMsg.len = 8;
  	CAN_TxMsg.format = idtype;
  	CAN_TxMsg.type = ftype;
  	CAN_wrMsg(CAN,&CAN_TxMsg,_mailIndex);   // transmit message
}
//Initialise Filters
void CAN_wrFilter (CAN_TypeDef *CAN,unsigned int id, unsigned char format, unsigned char mess_type)  {
  static unsigned short CAN_filterIdx;
         unsigned int   CAN_msgId     = 0;
	if(CAN==CAN2){
        CAN_filterIdx = 14;
        CAN1->FMR = (CAN1->FMR & 0xFFFF0000) | (CAN_filterIdx << 8) | 1;
		CAN1->FMR &= ~1; 
	}
	else{ CAN_filterIdx=0;       }
	CAN1->FMR = 1; 
  if (CAN_filterIdx > 27) {                       // check if Filter Memory is full
    return;
  }
                                                  // Setup identifier information
  if (format == STANDARD_FORMAT)  {               // Standard ID
      CAN_msgId  |= (unsigned int)(id << 21) | 0; //CAN_ID_STD;
  }  else  {                                      // Extended ID
      CAN_msgId  |= (unsigned int)(id <<  3) | 4; //CAN_ID_EXT;
  }
  if (mess_type == REMOTE_FRAME)	CAN_msgId  |= 2;

  CAN1->FA1R &=  ~(unsigned int)(1 << CAN_filterIdx); // deactivate filter

                                                  // initialize filter   
  CAN1->FS1R |= (unsigned int)(1 << CAN_filterIdx);// set 32-bit scale configuration
  CAN1->FM1R |= (unsigned int)(1 << CAN_filterIdx);// set 2 32-bit identifier list mode

  CAN1->sFilterRegister[CAN_filterIdx].FR1 = CAN_msgId; //  32-bit identifier
  CAN1->sFilterRegister[CAN_filterIdx].FR2 = CAN_msgId; //  32-bit identifier
    													   
  CAN1->FFA1R &= ~(unsigned int)(1 << CAN_filterIdx);  // assign filter to FIFO 0
  CAN1->FA1R  |=  (unsigned int)(1 << CAN_filterIdx);  // activate filter
  
    
  CAN_filterIdx += 1;                             // increase filter index
	CAN1->RF0R=RELEASE;
}
void filtersInit(CAN_TypeDef *CAN,int _id) {
  CAN1->FMR = 1;                                   //init mode for filters
  CAN_wrFilter (CAN,_id,EXTENDED_FORMAT,DATA_FRAME);      /* Enable reception of messages */
  CAN1->FMR &= ~1;                         // reset Initialisation mode for filter banks
																					/* leave init mode */
}
/*----------------------------------------------------------------------------
CAN Receive code
 *----------------------------------------------------------------------------*/

void canRead (CAN_TypeDef *CAN,CAN_msg *msg,int fifoIndex)  {
  if ((CAN->sFIFOMailBox[fifoIndex].RIR & 0x4)==0) { //CAN_ID_EXT) == 0) { // Standard ID
    msg->format = STANDARD_FORMAT;
    msg->id     = (unsigned int) 0x000007FF & (CAN->sFIFOMailBox[fifoIndex].RIR >> 21);
  }  else  {                                          // Extended ID
    msg->format = EXTENDED_FORMAT;
    msg->id     = (unsigned int) 0x1FFFFFFF & ((CAN->sFIFOMailBox[fifoIndex].RIR >> 3));
  }
                                                  // Read type information
  if ((CAN->sFIFOMailBox[fifoIndex].RIR & 0x2) ==0) { //CAN_RTR_REMOTE) == 0) {
    msg->type =   DATA_FRAME;                     // DATA   FRAME
  }  else  {
    msg->type = REMOTE_FRAME;                     // REMOTE FRAME
  }
                                                  // Read length (number of received bytes)
  msg->len = (unsigned char)0x0000000F & CAN->sFIFOMailBox[fifoIndex].RDTR;
                                                  // Read data bytes
  msg->data[0] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDLR);
  msg->data[1] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDLR >> 8);
  msg->data[2] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDLR >> 16);
  msg->data[3] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDLR >> 24);

  msg->data[4] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDHR);
  msg->data[5] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDHR >> 8);
  msg->data[6] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDHR >> 16);
  msg->data[7] = (unsigned int)0x000000FF & (CAN->sFIFOMailBox[fifoIndex].RDHR >> 24);
	
}

