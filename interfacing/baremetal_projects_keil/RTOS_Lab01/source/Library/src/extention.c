#include "i2c.h"
#include "gpio.h"
/*---------------------------------------------------------------------------*/
/** @brief I2C initialization.


@param[in] 
@param[in] 
*/
void extentionWrite(unsigned char adrs, unsigned char reg,unsigned char value){	
	I2C_Start(I2C2);	//see I2C_CR1 for code
	I2C_Addr(I2C2,adrs);// see I2C_DR for code
	I2C_Write(I2C2,reg);
	I2C_Write(I2C2,value);
	I2C_Stop(I2C2);
}
/*---------------------------------------------------------------------------*/
/** @brief I2C initialization.


@param[in] 
@param[in] 
*/
int extentionRead(unsigned char adrs, unsigned char reg){
	int r;
	I2C_Start(I2C2);	//see I2C_CR1 for code
	I2C_Addr (I2C2, adrs);// see I2C_DR for code
	I2C_Write(I2C2, reg);
	I2C_Start(I2C2);	//see I2C_CR1 for code
	I2C_Addr (I2C2, adrs|1);// see I2C_DR for code
	r= I2C_Read(I2C2, NOACKNOWLEDGE);
	I2C_Stop(I2C2);
	return r;
}
