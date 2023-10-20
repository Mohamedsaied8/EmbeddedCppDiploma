#include "main.h"
#include "freeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

xQueueHandle xQueue;
SemaphoreHandle_t  semaphore;


void ControlMotorsTask(void *pvParameter);
void ProducerTask(void *pvParameter);

int main()
{
	xQueue = xQueueCreate(1, sizeof(char));
	semaphore = xSemaphoreCreateMutex();
	if(xQueue != NULL)
	{
		RCC->APB2ENR = (1<<2); //Enable GPIOA
		GPIOA->CRL = (3<<4) | (3<<8); // configure PA1 = blue led as output pin
		xTaskCreate(ControlMotorsTask, "ControlMotorsTask", 300, NULL, 2, NULL);
		xTaskCreate(ProducerTask, "ProducerTask", 300, NULL, 2, NULL);
		vTaskStartScheduler();
	}
	else
	{

	}

	while(1);
	return 0;
}

void ControlMotorsTask(void *pvParameter)
{
	char control = 0;
	while(1)
	{
		xQueueReceive(xQueue, &control, portMAX_DELAY);
		if(control == 'w')
		{
			GPIOA->ODR ^=(1<<1);
		}
		else
		{

		}
		vTaskDelay(200/portTICK_RATE_MS);

	}
}

void ProducerTask(void *pvParameter)
{

	while(1)
	{
		char control = 'w';
		xQueueSendToBack(xQueue, &control, portMAX_DELAY);
		GPIOA->ODR ^=(1<<2);
		vTaskDelay(100/portTICK_RATE_MS);
	}
}
