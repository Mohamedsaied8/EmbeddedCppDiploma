
#include "lcd.h"
 
//---proper delay---//
void delay(int a)
{
    int i = 0;
    int f = 0;
    while(f < a)
    {
        while(i<60)
            {i++;}
        f++;
    }
}
 
//--- EN low then high then low---//
void PulseLCD()
{
    LCM_RSEN &= ~LCM_PIN_EN;
    delay(220);
    LCM_RSEN |= LCM_PIN_EN;
    delay(220);
    LCM_RSEN &= (~LCM_PIN_EN);
    delay(220);
}

//---send one byte to lcd---//
void SendByte(unsigned char ByteToSend, int IsData)
{
	if (IsData == 1)
        LCM_RSEN |= LCM_PIN_RS;
    else
        LCM_RSEN &= ~LCM_PIN_RS;
		
	// Output high nibble first
	LCM_OUT->BRR = LCM_PIN_D7;
	LCM_OUT->BRR = LCM_PIN_D6;
	LCM_OUT->BRR = LCM_PIN_D5;
	LCM_OUT->BRR = LCM_PIN_D4;
   // LCM_OUT |= (ByteToSend & 0xF0);
  if (ByteToSend & 0x80) LCM_OUT->BSRR = LCM_PIN_D7;
	if (ByteToSend & 0x40) LCM_OUT->BSRR = LCM_PIN_D6;
	if (ByteToSend & 0x20) LCM_OUT->BSRR = LCM_PIN_D5;
	if (ByteToSend & 0x10) LCM_OUT->BSRR = LCM_PIN_D4;
    
		  PulseLCD();

    // Output low nibble
	LCM_OUT->BRR = LCM_PIN_D7;
	LCM_OUT->BRR = LCM_PIN_D6;
	LCM_OUT->BRR = LCM_PIN_D5;
	LCM_OUT->BRR = LCM_PIN_D4;
		 
	if (ByteToSend & 0x08) LCM_OUT->BSRR = LCM_PIN_D7;
	if (ByteToSend & 0x04) LCM_OUT->BSRR = LCM_PIN_D6;
	if (ByteToSend & 0x02) LCM_OUT->BSRR = LCM_PIN_D5;
	if (ByteToSend & 0x01) LCM_OUT->BSRR = LCM_PIN_D4;
  PulseLCD();
		

}
 
//---move the cursor towards addresses---//
void Cursor(char Row, char Col)
{
   char address;
   if (Row == 0)
   address = 0;
   else
   address = 0x40;
   address |= Col;
   SendByte(0x80 | address, 0);
}
 
//---clear lcd---//
void ClearLCDScreen()
{
    SendByte(0x01, 0);
    SendByte(0x02, 0);
}
 
//---initialize and configure lcd with GPIO---//
void InitializeLCD(void)
{
		RCC->APB2ENR|=GPIOB_CLOCKEN |(1<<2);
	  GPIOA->CRH=0x33333333;
		GPIOB->CRH=0x33333333;
   // GPIOB->CRL = GPIO_Pin_0_OUTPUT | GPIO_Pin_1_OUTPUT| GPIO_Pin_4_OUTPUT | GPIO_Pin_5_OUTPUT| GPIO_Pin_6_OUTPUT| GPIO_Pin_7_OUTPUT;
 
   // LCM_OUT &= ~(LCM_PIN_MASK);
    delay(3200);
    delay(3200);
    delay(3200);
    LCM_RSEN &= ~LCM_PIN_RS;
    LCM_RSEN &= ~LCM_PIN_EN;
    LCM_OUT->ODR = LCM_PIN_D5;
    PulseLCD();
    SendByte(0x28, 0); // four bits command
    SendByte(0x0E, 0);
	    delay(320);
    SendByte(0x06, 0);
}
 
//---send string to LCD---//
void PrintStr(char *Text)
{
    char *c;
    c = Text;
    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, 1);
        c++;
    }
}