#ifndef CAN_H
#define CAN_H
#ifndef COMMON_H
#include "common.h"
#endif
#ifndef GPIO_H
#include "gpio.h"
#endif

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1
#define POLLING         !(1<<1)
#define INTERRUPT				 (1<<1)
#define DATA_FRAME       0
#define REMOTE_FRAME     1
#define MAILBOX0         0
#define MAILBOX1         1
#define MAILBOX2         2
#define FIFO0         0
#define FIFO1         1

#define CAN1_ReceiveFIFO						CAN1->RF0R
#define CAN2_ReceiveFIFO						CAN2->RF0R
#define RELEASE                      (1<<5)

typedef struct  {
  unsigned int   id;                 // 29 bit identifier
  char           data[8];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

#define CAN1                  ((CAN_TypeDef    *) CAN1_BASE    )
#define CAN2                  ((CAN_TypeDef    *) CAN2_BASE    )

/*------------------------ Controller Area Network ---------------------------*/

typedef struct
{
  __IO uint32_t TIR;
  __IO uint32_t TDTR;
  __IO uint32_t TDLR;
  __IO uint32_t TDHR;
} CAN_TxMailBox_TypeDef;

typedef struct
{
  __IO uint32_t RIR;
  __IO uint32_t RDTR;
  __IO uint32_t RDLR;
  __IO uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;

typedef struct
{
  __IO uint32_t FR1;
  __IO uint32_t FR2;
} CAN_FilterRegister_TypeDef;

typedef struct
{
  __IO uint32_t MCR;
  __IO uint32_t MSR;
  __IO uint32_t TSR;
  __IO uint32_t RF0R;
  __IO uint32_t RF1R;
  __IO uint32_t IER;
  __IO uint32_t ESR;
  __IO uint32_t BTR;
       uint32_t RESERVED0[88];
  CAN_TxMailBox_TypeDef      sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];
       uint32_t RESERVED1[12];
  __IO uint32_t FMR;
  __IO uint32_t FM1R;
       uint32_t RESERVED2;
  __IO uint32_t FS1R;
       uint32_t RESERVED3;
  __IO uint32_t FFA1R;
       uint32_t RESERVED4;
  __IO uint32_t FA1R;
       uint32_t RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[28];
} CAN_TypeDef;
extern CAN_msg  CAN_TxMsg, CAN_RxMsg;

//Functions Proto-types
void canInit(CAN_TypeDef *CAN,int _mode );
void CAN_wrMsg (CAN_TypeDef *CAN,CAN_msg *msg,int mailIndex);
void canTransmit(CAN_TypeDef *CAN,int id,char idtype,char ftype, unsigned char *m,int _mailIndex);
void CAN_wrFilter (CAN_TypeDef *CAN,unsigned int id, unsigned char format, unsigned char mess_type);
void filtersInit(CAN_TypeDef *CAN,int _id);
void canRead(CAN_TypeDef *CAN,CAN_msg *msg,int fifoIndex);
#endif
