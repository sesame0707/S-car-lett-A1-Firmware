/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */
GPIO_PinState ButtonStateCurrent;
GPIO_PinState ButtonStateLast = GPIO_PIN_RESET;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED1_Task */
osThreadId_t LED1_TaskHandle;
const osThreadAttr_t LED1_Task_attributes = {
  .name = "LED1_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED2_Task */
osThreadId_t LED2_TaskHandle;
const osThreadAttr_t LED2_Task_attributes = {
  .name = "LED2_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BUT1_Task */
osThreadId_t BUT1_TaskHandle;
const osThreadAttr_t BUT1_Task_attributes = {
  .name = "BUT1_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED3_Task */
osThreadId_t LED3_TaskHandle;
const osThreadAttr_t LED3_Task_attributes = {
  .name = "LED3_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartLED1_Task(void *argument);
void StartLED2_Task(void *argument);
void StartBUT1_Task(void *argument);
void StartLED3_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of LED1_Task */
  LED1_TaskHandle = osThreadNew(StartLED1_Task, NULL, &LED1_Task_attributes);

  /* creation of LED2_Task */
  LED2_TaskHandle = osThreadNew(StartLED2_Task, NULL, &LED2_Task_attributes);

  /* creation of BUT1_Task */
  BUT1_TaskHandle = osThreadNew(StartBUT1_Task, NULL, &BUT1_Task_attributes);

  /* creation of LED3_Task */
  LED3_TaskHandle = osThreadNew(StartLED3_Task, NULL, &LED3_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartLED1_Task */
/**
* @brief Function implementing the LED1_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED1_Task */
void StartLED1_Task(void *argument)
{
  /* USER CODE BEGIN StartLED1_Task */
  /* Infinite loop */
  for(;;)
  {
	  if(ButtonStateCurrent == ButtonStateLast)
	  {
		  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		  osDelay(100);
	  }
  }
  /* USER CODE END StartLED1_Task */
}

/* USER CODE BEGIN Header_StartLED2_Task */
/**
* @brief Function implementing the LED2_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED2_Task */
void StartLED2_Task(void *argument)
{
  /* USER CODE BEGIN StartLED2_Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	  osDelay(300);
  }
  /* USER CODE END StartLED2_Task */
}

/* USER CODE BEGIN Header_StartBUT1_Task */
/**
* @brief Function implementing the BUT1_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBUT1_Task */
void StartBUT1_Task(void *argument)
{
  /* USER CODE BEGIN StartBUT1_Task */
  /* Infinite loop */
  for(;;)
  {
	  ButtonStateCurrent = HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin);
  }
  /* USER CODE END StartBUT1_Task */
}

/* USER CODE BEGIN Header_StartLED3_Task */
/**
* @brief Function implementing the LED3_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED3_Task */
void StartLED3_Task(void *argument)
{
  /* USER CODE BEGIN StartLED3_Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	  osDelay(900);
  }
  /* USER CODE END StartLED3_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

