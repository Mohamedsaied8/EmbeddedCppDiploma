/*
 * adc.h
 *
 *  Created on: Jan 14, 2023
 *      Author: MMohamedSaid
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_


class ADC
{
public:

	typedef enum ADCInstance: uint32_t
	{
		ADC_1 = ADC1_BASE,
		ADC_2 = ADC2_BASE,
	};

	ADC()
	{
		if(this == reinterpret_cast<ADC*>(ADCInstance::ADC_1))
		{
			ADC1_Init();
		}
		else if(this == reinterpret_cast<ADC*>(ADCInstance::ADC_2))
		{
			ADC2_Init();
		}
	}

	//placement new
	void* operator new(size_t, ADCInstance adc)
	{
		return reinterpret_cast<void*>(adc);
	}
	//ADC init
	void ADC1_Init()
	{
		//MODE:CFG Input=00 : Analog=00
		GPIOA->CRL=0x44444400;
		//ADC configure clock to 14Mhz
		RCC-> CFGR &= ~(3<<14);	//ensure ADCPRE is zero
		RCC-> CFGR |= (2<<14);  //14mHZ

		//A1configure pin for ADC as an input alternate
		//select Reqular Group from Control Register

		// Select the required Channel ADC12_IN1
		 SQR1|=0x00000180;
		 SQR2|=0;
		 SQR3|=0x00000001;
		//Sampling Time Selection ADC12_IN1 = PA1
		 SMPR1|=(6<<0);

		 CR2 |= (7<<17);	//select SWSTART as trigger
		 CR2 |= (1<<20);	//enable external trigger -

		//Right Alignment
		 CR2 &= ~(1<<11);	//right alignment -

		 CR2 |= (1<<1);	//continuous conversion
		//adc on
	    CR2 |= (1<<0);	//ADC on

		 CR2 |= (1<<3);	// Reset calibration
		while (ADC1->CR2 & (1<<3));	// wait until reset finished
	    CR2 |= (1<<2);	// start calibration
	   while ( CR2 & (1<<2));	// wait unt
	}

	void ADC2_Init()
	{
		//MODE:CFG Input=00 : Analog=00
		GPIOA->CRL|=0x44444400;
		//ADC configure clock to 14Mhz
		RCC-> CFGR &= ~(3<<14);	//ensure ADCPRE is zero
		RCC-> CFGR |= (2<<14);  //14mHZ

		//A1configure pin for ADC as an input alternate
		//select Reqular Group from Control Register

		// Select the required Channel ADC12_IN0
		 SQR1|=0x00000180;
		 SQR2|=0;
		 SQR3|=0x00000000;
		//Sampling Time Selection ADC12_IN0 = PA0 @ 1.5 cycles
		 SMPR1|=(6<<0);

		 CR2 |= (7<<17);	//select SWSTART as trigger
		 CR2 |= (1<<20);	//enable external trigger -

		//Right Alignment
		 CR2 &= ~(1<<11);	//right alignment -

		 CR2 |= (1<<1);	//continuous conversion
		//adc on
		 CR2 |= (1<<0);	//ADC on

		 CR2 |= (1<<3);	// Reset calibration
		while ( CR2 & (1<<3));	// wait until reset finished
		 CR2 |= (1<<2);	// start calibration
		while ( CR2 & (1<<2));	// wait until calibration finished
	}
	//ADC Read
	int ADC_Read()
	{
		static int ADC_value=0;
		CR2 |= (1<<22); // start SW conversion
		while (!(SR & (1<<1)));	//EOC
		ADC_value =  DR;
		//reset EOC Flag
		SR &= ~(1<<1);
		return ADC_value;
	}

private:
	  volatile uint32_t SR;
	  volatile uint32_t CR1;
	  volatile uint32_t CR2;
	  volatile uint32_t SMPR1;
	  volatile uint32_t SMPR2;
	  volatile uint32_t JOFR1;
	  volatile uint32_t JOFR2;
	  volatile uint32_t JOFR3;
	  volatile uint32_t JOFR4;
	  volatile uint32_t HTR;
	  volatile uint32_t LTR;
	  volatile uint32_t SQR1;
	  volatile uint32_t SQR2;
	  volatile uint32_t SQR3;
	  volatile uint32_t JSQR;
	  volatile uint32_t JDR1;
	  volatile uint32_t JDR2;
	  volatile uint32_t JDR3;
	  volatile uint32_t JDR4;
	  volatile uint32_t DR;
};



#endif /* INC_ADC_H_ */
