#ifndef MAINHEADER_H
#define MAINHEADER_H

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#define vPortSVCHandler 						SVC_Handler
#define xPortPendSVHandler 					PendSV_Handler
#define xPortSysTickHandler 				SysTick_Handler
#define vUARTInterruptHandler				USART1_IRQHandler	
#define vTimer2IntHandler						TIM2_IRQHandler


extern xTaskHandle menu_handle,lcd_flash_handle;
//Semaphore deceleration
extern xQueueSetHandle standardModeSemaphore,programmingModeSemaphore,menuSemaphore,passwordSemaphore,pressedSemaphore,extentionInputSemaphore,outputSemaphore,extentionOutputSemaphore;
//Queue deceleration
extern xQueueHandle LCDQueue,LCDFlashQueue;

extern char message1[33];
//Tasks
void inputTask(void *pvParameter);
void outputTask(void *pvParameter);
void extentionWriteTask(void *pvParameter);
void extentionReadTask(void *pvParameter);
void standardMode(void *pvParameter);
void LCDTask(void *pvParameter);
//Functions prototype
void initclk(void);
#endif
