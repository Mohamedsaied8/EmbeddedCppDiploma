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

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xQueue;

void vBlueLedTask( void *pvParameters )
{
	int recv = 0;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{

		xQueueReceive(xQueue, &recv, 1000/portTICK_PERIOD_MS);

		if(recv == 8)
		{
			GPIOA->ODR ^= (1<<2);
		}


		/*
		 * Blocking Delay
		 * dummy loop
		 * polling on something
		 * HAL_Delay
		 *
		 *
		 * Non-Blocking Delay
		 * Timer interrupt
		 * in FreeRTOS : vTaskDelay
		 *
		 */
		vTaskDelay(500/portTICK_PERIOD_MS);

	}
}

void vGreenLedTask( void *pvParameters )
{
	int count =0;
	/* As per most tasks, this 21task is implemented in an infinite loop. */
	for( ;; )
	{
		GPIOA->ODR ^= (1<<1);
		count = 8;
		xQueueSendToBack( xQueue, count, 1000/portMAX_DELAY);

		vTaskDelay(1000/portTICK_PERIOD_MS);

	}
}



int main(void)
{
	RCC->APB2ENR = (1<<2);
	GPIOA->CRL = (3<<8) | (3<<4);

	xQueue =  xQueueCreate( 1, sizeof(int) );

	if(xQueue != NULL)
	{
		/* Create one of the two tasks. */
		xTaskCreate(	vGreenLedTask,		/* Pointer to the function that implements the task. */
						"Task 2",	/* Text name for the task.  This is to facilitate debugging only. */
						300,		/* Stack depth in words. */
						NULL,		/* We are not using the task parameter. */
						2,			/* This task will run at priority 2. */
						NULL );		/* We are not using the task handle. */

		/* Create one of the two tasks. */
		xTaskCreate(	vBlueLedTask,		/* Pointer to the function that implements the task. */
						"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
						300,		/* Stack depth in words. */
						NULL,		/* We are not using the task parameter. */
						1,			/* This task will run at priority 1. */
						NULL );		/* We are not using the task handle. */


	}

	/* Start the scheduler so our tasks start executing. */

   vTaskStartScheduler();

  while (1)
  {

  }

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
