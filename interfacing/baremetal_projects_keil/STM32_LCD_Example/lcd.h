#include <stm32f10x.h>
#define GPIOB_CLOCKEN      (1<<3)

// LCD control lines (must be on the same port) 
#define GPIO_Pin_0              0x0001//            0000 0000 0000 0001 
#define GPIO_Pin_1              0x0002//            0000 0000 0000 0010
#define GPIO_Pin_2              0x0004//            0000 0000 0000 0100
#define GPIO_Pin_3              0x0008//            0000 0000 0000 1000
#define GPIO_Pin_4              0x0010//            0000 0000 0001 0000
#define GPIO_Pin_5              0x0020//            0000 0000 0010 0000
#define GPIO_Pin_6              0x0040//            0000 0000 0100 0000
#define GPIO_Pin_7              0x0080//            0000 0000 1000 0000
#define GPIO_Pin_8              0x0100//            0000 0000 0000 0000
#define GPIO_Pin_9              0x0200//            0000 0000 0000 0000
#define GPIO_Pin_10             0x0400//            0000 0000 0000 0000
#define GPIO_Pin_11             0x0800//            0000 0000 0000 0000
#define GPIO_Pin_12             0x1000//            0000 0000 0000 0000
#define GPIO_Pin_13             0x2000//            0000 0000 0000 0000
#define GPIO_Pin_14             0x4000//            0000 0000 0000 0000
#define GPIO_Pin_15             0x8000//            0000 0000 0000 0000

//GPIO->CRL
#define GPIO_CRL_OUTPUT         0x33333333
#define GPIO_Pin_0_OUTPUT 			(3<<0)
#define GPIO_Pin_1_OUTPUT 			(3<<4)
#define GPIO_Pin_2_OUTPUT 			(3<<8)
#define GPIO_Pin_3_OUTPUT 			(3<<12)
#define GPIO_Pin_4_OUTPUT 			(3<<16)
#define GPIO_Pin_5_OUTPUT 			(3<<20)
#define GPIO_Pin_6_OUTPUT 			(3<<24)
#define GPIO_Pin_7_OUTPUT 			(3<<28)




// Pin definition
//#define LCD16X2_PIN_RW             GPIO_Pin_13

#define     LCM_RSEN         			GPIOB->ODR
#define     LCM_OUT               GPIOA
#define     LCM_PIN_RS            GPIO_Pin_12          // PA8
#define     LCM_PIN_EN            GPIO_Pin_14         // PA9
#define     LCM_PIN_D7            GPIO_Pin_11          // PB7 15
#define     LCM_PIN_D6            GPIO_Pin_10         // PB6  14
#define     LCM_PIN_D5            GPIO_Pin_9          // PB5  13
#define     LCM_PIN_D4            GPIO_Pin_8          // PB4 12
#define     LCM_PIN_MASK 				 (LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4)

// Pin definition
//#define LCD16X2_PIN_RW             GPIO_Pin_13


void delay(int a);



void PulseLCD();

void SendByte(unsigned char ByteToSend, int IsData);


void Cursor(char Row, char Col);


void ClearLCDScreen();



void InitializeLCD(void);

void PrintStr(char *Text);
