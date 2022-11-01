/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

		//00010000>>4  & 1 = 1
#define GET_BIT(reg,bit)	(reg>>bit&1)
#define SET_BIT(reg,bit)	reg |= (1<<bit)
#define CLEAR_BIT(reg,bit)	reg &=~ (1<<bit)
#define TOGGLE_BIT(reg,bit) reg ^= (1<<bit) //XOR

class Button
{
public:
	Button(GPIO_TypeDef * port, uint16_t pin):button_port(port),btn_pin(pin)
	{
		RCC->APB2ENR |= (1<<3); //Enable Clock for GPIOB
		button_port->CRL = (4<<16); //configure PB4 as input pin
	}
	uint32_t GetButtonStatus()
	{
		return GET_BIT(button_port->IDR ,btn_pin);
	}
private:
	GPIO_TypeDef * button_port;
	uint16_t btn_pin{0};

};

class LED
{
public:
	LED()
	{
		RCC->APB2ENR = (1<<2);
		GPIOA->CRL = (3<<4); //PA1 as an output PIN
	}
	void LED_ON()
	{
		GPIOA->ODR = (1<<1); // Blue Led
	}
	void LED_OFF()
	{
		GPIOA->ODR &= ~(1<<1);
	}
};
struct MotorType
{
	GPIO_TypeDef * motor_pin1_port;
	GPIO_TypeDef * motor_pin2_port;
	GPIO_TypeDef * enable_port;
	uint8_t input_1{0};
	uint8_t input_2{0};
	uint8_t enable{0};
};
class Motor
{
public:
	Motor( MotorType *motor) : m_motor(motor)
	{
		Motor_Stop();
	}

	void Motor_CW()
	{
		SET_BIT(m_motor->motor_pin1_port->ODR, m_motor->input_1);
		CLEAR_BIT(m_motor->motor_pin1_port->ODR ,m_motor->input_2);
		SET_BIT(m_motor->enable_port->ODR, m_motor->enable);

	}
	void Motor_CCW()
	{

		CLEAR_BIT(m_motor->motor_pin1_port->ODR, m_motor->input_1);
		SET_BIT(m_motor->motor_pin1_port->ODR ,m_motor->input_2);
		SET_BIT(m_motor->enable_port->ODR, m_motor->enable);

	}
	void Motor_Stop()
	{
		CLEAR_BIT(m_motor->motor_pin1_port->ODR, m_motor->input_1);
		CLEAR_BIT(m_motor->motor_pin1_port->ODR ,m_motor->input_2);
		CLEAR_BIT(m_motor->enable_port->ODR, m_motor->enable);
	}
private:
	 MotorType *m_motor; //pimpl idiom
};

class Robot{
public:
	Robot(Motor m1, Motor m2) : motor1(m1), motor2(m2)
	{
		motor1.Motor_Stop();
		motor2.Motor_Stop();
	}
	void Forward()
	{
		motor1.Motor_CW();
		motor2.Motor_CCW();
	}
	void Backward()
	{
		motor1.Motor_CCW();
		motor2.Motor_CW();
	}
	void Right()
	{
		motor1.Motor_CW();
		motor2.Motor_Stop();
	}
	void Left()
	{
		motor1.Motor_Stop();
		motor2.Motor_CW();
	}
private:
	Motor motor1;
	Motor motor2;
};

MotorType motor_config
{
	GPIOC,
	GPIOC,
	GPIOC,
	13,
	14,
	15
};

int main(void)
{

	LED blue_led;
	Button button(GPIOB,4);

	RCC->APB2ENR = (1<<4) | (1<<3); //Enable Clock for GPIOC and GPIOB
	GPIOC->CRH = 0x33333333;
	//GPIOB->CRL = (3<<4);

	Motor motor1(&motor_config);


  while (1)
  {
	  if(button.GetButtonStatus()==0)
	  {
		  motor1.Motor_CW();
	  }
	  else{
		  motor1.Motor_CCW();

	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
