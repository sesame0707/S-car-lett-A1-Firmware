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
extern uint8_t rx_buffer[];

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_dispatcher */
osThreadId_t API_dispatcherHandle;
const osThreadAttr_t API_dispatcher_attributes = {
  .name = "API_dispatcher",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartAPI_dispatcher(void *argument);

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

  /* creation of API_dispatcher */
  API_dispatcherHandle = osThreadNew(StartAPI_dispatcher, NULL, &API_dispatcher_attributes);

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
//	uint8_t data[] = "A\r\n";

  /* Infinite loop */
  for(;;)
  {
	  vTaskDelete(NULL);
//	  osDelay(1);
//	  HAL_UART_Transmit_IT ( &huart1, data, sizeof (data) );

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartAPI_dispatcher */
/**
* @brief Function implementing the API_dispatcher thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_dispatcher */
void StartAPI_dispatcher(void *argument)
{
  /* USER CODE BEGIN StartAPI_dispatcher */
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);	// suspend itself
//	  ulTaskNotifyTake(pdTRUE, (TickType_t) portMAX_DELAY);

	  switch(rx_buffer[0]) {
	  	case 0x1:
	  		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
	  		break;
	  	case 0x2:
	  		HAL_GPIO_TogglePin(API_START_ENGIN_LEDs_GPIO_Port, API_START_ENGIN_LEDs_Pin);
	  		break;
	  	case 0x3:
	  		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	  		break;
	  	case 0x4:
	  		HAL_GPIO_TogglePin(API_TURN_LEFT_LEDs_GPIO_Port, API_TURN_LEFT_LEDs_Pin);
	  		break;
	  	case 0x5:
	  		HAL_GPIO_TogglePin(API_TURN_RIGHT_LEDs_GPIO_Port, API_TURN_RIGHT_LEDs_Pin);
	  		break;
	  	case 0x6:
	  		HAL_GPIO_TogglePin(API_TURN_LEFT_LEDs_GPIO_Port, API_TURN_LEFT_LEDs_Pin);
	  		HAL_GPIO_TogglePin(API_TURN_RIGHT_LEDs_GPIO_Port, API_TURN_RIGHT_LEDs_Pin);
	  		break;
	  	case 0x7:
	  		HAL_GPIO_TogglePin(API_TURN_RIGHT_LEDs_GPIO_Port, API_TURN_RIGHT_LEDs_Pin);
	  		HAL_GPIO_TogglePin(API_TURN_LEFT_LEDs_GPIO_Port, API_TURN_LEFT_LEDs_Pin);
	  		break;
	  	default:
	  	}
  }
  /* USER CODE END StartAPI_dispatcher */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

