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
GPIO_PinState API_START_ENGIN_ButtonStateCurrent;
GPIO_PinState API_START_ENGIN_ButtonStateLast = GPIO_PIN_RESET;

GPIO_PinState API_BRAKE_ButtonStateCurrent;
GPIO_PinState API_BRAKE_ButtonStateLast = GPIO_PIN_RESET;

GPIO_PinState API_WITHDRAW_ButtonStateCurrent;
GPIO_PinState API_WITHDRAW_ButtonStateLast = GPIO_PIN_RESET;

GPIO_PinState API_TURN_RIGHT_ButtonStateCurrent;
GPIO_PinState API_TURN_RIGHT_ButtonStateLast = GPIO_PIN_RESET;

GPIO_PinState API_TURN_LEFT_ButtonStateCurrent;
GPIO_PinState API_TURN_LEFT_ButtonStateLast = GPIO_PIN_RESET;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_START_ENGIN */
osThreadId_t API_START_ENGINHandle;
const osThreadAttr_t API_START_ENGIN_attributes = {
  .name = "API_START_ENGIN",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_BRAKE */
osThreadId_t API_BRAKEHandle;
const osThreadAttr_t API_BRAKE_attributes = {
  .name = "API_BRAKE",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_WITHDRAW */
osThreadId_t API_WITHDRAWHandle;
const osThreadAttr_t API_WITHDRAW_attributes = {
  .name = "API_WITHDRAW",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_TURN_LEFT */
osThreadId_t API_TURN_LEFTHandle;
const osThreadAttr_t API_TURN_LEFT_attributes = {
  .name = "API_TURN_LEFT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for API_TURN_RIGHT */
osThreadId_t API_TURN_RIGHTHandle;
const osThreadAttr_t API_TURN_RIGHT_attributes = {
  .name = "API_TURN_RIGHT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartAPI_START_ENGIN(void *argument);
void StartAPI_BRAKE(void *argument);
void StartAPI_WITHDRAW(void *argument);
void StartAPI_TURN_LEFT(void *argument);
void StartAPI_TURN_RIGHT(void *argument);

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

  /* creation of API_START_ENGIN */
  API_START_ENGINHandle = osThreadNew(StartAPI_START_ENGIN, NULL, &API_START_ENGIN_attributes);

  /* creation of API_BRAKE */
  API_BRAKEHandle = osThreadNew(StartAPI_BRAKE, NULL, &API_BRAKE_attributes);

  /* creation of API_WITHDRAW */
  API_WITHDRAWHandle = osThreadNew(StartAPI_WITHDRAW, NULL, &API_WITHDRAW_attributes);

  /* creation of API_TURN_LEFT */
  API_TURN_LEFTHandle = osThreadNew(StartAPI_TURN_LEFT, NULL, &API_TURN_LEFT_attributes);

  /* creation of API_TURN_RIGHT */
  API_TURN_RIGHTHandle = osThreadNew(StartAPI_TURN_RIGHT, NULL, &API_TURN_RIGHT_attributes);

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

/* USER CODE BEGIN Header_StartAPI_START_ENGIN */
/**
* @brief Function implementing the API_START_ENGIN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_START_ENGIN */
void StartAPI_START_ENGIN(void *argument)
{
  /* USER CODE BEGIN StartAPI_START_ENGIN */
  /* Infinite loop */
  for(;;)
  {
	  API_START_ENGIN_ButtonStateCurrent = HAL_GPIO_ReadPin(API_START_ENGIN_But_GPIO_Port, API_START_ENGIN_But_Pin);
	  if(API_START_ENGIN_ButtonStateCurrent != API_START_ENGIN_ButtonStateLast)
	  {
		  HAL_GPIO_TogglePin(API_START_ENGIN_LEDs_GPIO_Port, API_START_ENGIN_LEDs_Pin);
		  osDelay(100);
	  }
  }
  /* USER CODE END StartAPI_START_ENGIN */
}

/* USER CODE BEGIN Header_StartAPI_BRAKE */
/**
* @brief Function implementing the API_BRAKE thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_BRAKE */
void StartAPI_BRAKE(void *argument)
{
  /* USER CODE BEGIN StartAPI_BRAKE */
  /* Infinite loop */
  for(;;)
  {
	  API_BRAKE_ButtonStateCurrent = HAL_GPIO_ReadPin(API_BRAKE_But_GPIO_Port, API_BRAKE_But_Pin);
	  if(API_BRAKE_ButtonStateCurrent != API_BRAKE_ButtonStateLast)
	  {
		  HAL_GPIO_TogglePin(API_BRAKE_LEDs_GPIO_Port, API_BRAKE_LEDs_Pin);
		  osDelay(100);
		  API_BRAKE_ButtonStateLast = API_BRAKE_ButtonStateCurrent;
	  }
  }
  /* USER CODE END StartAPI_BRAKE */
}

/* USER CODE BEGIN Header_StartAPI_WITHDRAW */
/**
* @brief Function implementing the API_WITHDRAW thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_WITHDRAW */
void StartAPI_WITHDRAW(void *argument)
{
  /* USER CODE BEGIN StartAPI_WITHDRAW */
  /* Infinite loop */
  for(;;)
  {
	  API_WITHDRAW_ButtonStateCurrent = HAL_GPIO_ReadPin(API_WITHDRAW_But_GPIO_Port, API_WITHDRAW_But_Pin);
	  if(API_WITHDRAW_ButtonStateCurrent != API_WITHDRAW_ButtonStateLast)
	  {
		  HAL_GPIO_TogglePin(API_WITHDRAW_LEDs_GPIO_Port, API_WITHDRAW_LEDs_Pin);
		  osDelay(100);
		  API_WITHDRAW_ButtonStateLast = API_WITHDRAW_ButtonStateCurrent;
	  }
  }
  /* USER CODE END StartAPI_WITHDRAW */
}

/* USER CODE BEGIN Header_StartAPI_TURN_LEFT */
/**
* @brief Function implementing the API_TURN_LEFT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_TURN_LEFT */
void StartAPI_TURN_LEFT(void *argument)
{
  /* USER CODE BEGIN StartAPI_TURN_LEFT */
  /* Infinite loop */
  for(;;)
  {
	  API_TURN_LEFT_ButtonStateCurrent = HAL_GPIO_ReadPin(API_TURN_LEFT_But_GPIO_Port, API_TURN_LEFT_But_Pin);
	  if(API_TURN_LEFT_ButtonStateCurrent != API_TURN_LEFT_ButtonStateLast)
	  {
		  for(int i=0; i<6; i++)
		  {
			  HAL_GPIO_TogglePin(API_TURN_LEFT_LEDs_GPIO_Port, API_TURN_LEFT_LEDs_Pin);
			  osDelay(200);
		  }
	  }
  }
  /* USER CODE END StartAPI_TURN_LEFT */
}

/* USER CODE BEGIN Header_StartAPI_TURN_RIGHT */
/**
* @brief Function implementing the API_TURN_RIGHT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAPI_TURN_RIGHT */
void StartAPI_TURN_RIGHT(void *argument)
{
  /* USER CODE BEGIN StartAPI_TURN_RIGHT */
  /* Infinite loop */
  for(;;)
  {
	  API_TURN_RIGHT_ButtonStateCurrent = HAL_GPIO_ReadPin(API_TURN_RIGHT_But_GPIO_Port, API_TURN_RIGHT_But_Pin);
	  	  if(API_TURN_RIGHT_ButtonStateCurrent != API_TURN_RIGHT_ButtonStateLast)
	  	  {
	  		  for(int i=0; i<6; i++)
	  		  {
	  			  HAL_GPIO_TogglePin(API_TURN_RIGHT_LEDs_GPIO_Port, API_TURN_RIGHT_LEDs_Pin);
	  			  osDelay(200);
	  		  }
	  	  }
  }
  /* USER CODE END StartAPI_TURN_RIGHT */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

