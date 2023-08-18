/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
extern "C"
{
#include "Timer.h"

}

#include "timer_driver.h"

volatile uint32_t duty;
volatile uint32_t period;


void Clock_72(){
	//Adding wait states to memory reads.
	FLASH->ACR	= 0x12;	// for system clock between 48 and 72MHz
	RCC->CR |= 1<<16;	//HSE on
	while (!(RCC->CR & (1<<17)));	//wait until HSE ready
	RCC->CR |= 1<<26;	//PLL2 on
	RCC->CFGR |= (1<<16);
	RCC->CFGR |= 7<<18;	// mult by 9	--->72MHz
	RCC->CFGR |= 1<<10;	//APB1 = 36MHz. See bus clocks.
	RCC->CR |= 1<<24;	//enable PLL
	while (!(RCC->CR & (1<<25)));	//wait until locked
	RCC->CFGR |= 2;	//PLL as clock source
}

/*************************************************
* Main code starts from here
*************************************************/

class Servo
{
public:
	Servo()
	{
		 servo = new(TIMER::TIM_1) TIMER;
		 servo->pwmInit(PERIOD);
	}


	void write(int angle)
	{
		servo->pwmWrite(PERIOD,angle);
	}

private:
	const uint32_t PERIOD = 20000;
	TIMER  *servo = nullptr;
};

/*
class RobotArm
{
public:
	RobotArm();

	void receiveCommand();
	void MoveArmYAW(int angle);
	void MoveArmRoll(int angle);
	void MoveArmPitch(int angle);



private:
	void moveServo(Servo servo,int angle);
	void moveBase(Direction dir);

	Servo servo_1;
	DC_MOTOR base_motor;
	Bluetooth bt;
};
*/
int main(void)
{

	period = 20000;
	// Set clock to 72 MHz
	Clock_72();

	//Tim1_Init(period);
	Servo servo;


	while(1)
	{
		uint32_t j;
		servo.write(50);
		//pwmWrite(period,50);

		for(j=0;j>9000000;j++);

	}

	// Should never reach here
	return 0;
}
