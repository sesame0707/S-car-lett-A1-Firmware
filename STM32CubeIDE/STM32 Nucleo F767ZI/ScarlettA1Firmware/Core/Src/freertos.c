/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
/* System libraries */
#include <string.h>

/* External libraries */
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"

/* Own headers */
#include "commonStrings.h"
#include "commonVariables.h"
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
/* Definitions for OLEDTask */
osThreadId_t OLEDTaskHandle;
const osThreadAttr_t OLEDTask_attributes = {
  .name = "OLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DispatcherTask */
osThreadId_t DispatcherTaskHandle;
const osThreadAttr_t DispatcherTask_attributes = {
  .name = "DispatcherTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for StopTask */
osThreadId_t StopTaskHandle;
const osThreadAttr_t StopTask_attributes = {
  .name = "StopTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DrivingLightsTa */
osThreadId_t DrivingLightsTaHandle;
const osThreadAttr_t DrivingLightsTa_attributes = {
  .name = "DrivingLightsTa",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LEDStripeTask */
osThreadId_t LEDStripeTaskHandle;
const osThreadAttr_t LEDStripeTask_attributes = {
  .name = "LEDStripeTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LeftBlinkersTas */
osThreadId_t LeftBlinkersTasHandle;
const osThreadAttr_t LeftBlinkersTas_attributes = {
  .name = "LeftBlinkersTas",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RightBlinkersTa */
osThreadId_t RightBlinkersTaHandle;
const osThreadAttr_t RightBlinkersTa_attributes = {
  .name = "RightBlinkersTa",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ParkLeftTask */
osThreadId_t ParkLeftTaskHandle;
const osThreadAttr_t ParkLeftTask_attributes = {
  .name = "ParkLeftTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ParkRightTask */
osThreadId_t ParkRightTaskHandle;
const osThreadAttr_t ParkRightTask_attributes = {
  .name = "ParkRightTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for AccelerateTask */
osThreadId_t AccelerateTaskHandle;
const osThreadAttr_t AccelerateTask_attributes = {
  .name = "AccelerateTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DecelerateTask */
osThreadId_t DecelerateTaskHandle;
const osThreadAttr_t DecelerateTask_attributes = {
  .name = "DecelerateTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TurnLeftTask */
osThreadId_t TurnLeftTaskHandle;
const osThreadAttr_t TurnLeftTask_attributes = {
  .name = "TurnLeftTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TurnRightTask */
osThreadId_t TurnRightTaskHandle;
const osThreadAttr_t TurnRightTask_attributes = {
  .name = "TurnRightTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ConnectionTask */
osThreadId_t ConnectionTaskHandle;
const osThreadAttr_t ConnectionTask_attributes = {
  .name = "ConnectionTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartOLEDTask(void *argument);
void StartDispatcherTask(void *argument);
void StartStopTask(void *argument);
void StartDrivingLightsTask(void *argument);
void StartLEDStripeTask(void *argument);
void StartLeftBlinkersTask(void *argument);
void StartRightBlinkersTask(void *argument);
void StartParkLeftTask(void *argument);
void StartParkRightTask(void *argument);
void StartAccelerateTask(void *argument);
void StartDecelerateTask(void *argument);
void StartTurnLeftTask(void *argument);
void StartTurnRightTask(void *argument);
void StartConnectionTask(void *argument);

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
  /* creation of OLEDTask */
  OLEDTaskHandle = osThreadNew(StartOLEDTask, NULL, &OLEDTask_attributes);

  /* creation of DispatcherTask */
  DispatcherTaskHandle = osThreadNew(StartDispatcherTask, NULL, &DispatcherTask_attributes);

  /* creation of StopTask */
  StopTaskHandle = osThreadNew(StartStopTask, NULL, &StopTask_attributes);

  /* creation of DrivingLightsTa */
  DrivingLightsTaHandle = osThreadNew(StartDrivingLightsTask, NULL, &DrivingLightsTa_attributes);

  /* creation of LEDStripeTask */
  LEDStripeTaskHandle = osThreadNew(StartLEDStripeTask, NULL, &LEDStripeTask_attributes);

  /* creation of LeftBlinkersTas */
  LeftBlinkersTasHandle = osThreadNew(StartLeftBlinkersTask, NULL, &LeftBlinkersTas_attributes);

  /* creation of RightBlinkersTa */
  RightBlinkersTaHandle = osThreadNew(StartRightBlinkersTask, NULL, &RightBlinkersTa_attributes);

  /* creation of ParkLeftTask */
  ParkLeftTaskHandle = osThreadNew(StartParkLeftTask, NULL, &ParkLeftTask_attributes);

  /* creation of ParkRightTask */
  ParkRightTaskHandle = osThreadNew(StartParkRightTask, NULL, &ParkRightTask_attributes);

  /* creation of AccelerateTask */
  AccelerateTaskHandle = osThreadNew(StartAccelerateTask, NULL, &AccelerateTask_attributes);

  /* creation of DecelerateTask */
  DecelerateTaskHandle = osThreadNew(StartDecelerateTask, NULL, &DecelerateTask_attributes);

  /* creation of TurnLeftTask */
  TurnLeftTaskHandle = osThreadNew(StartTurnLeftTask, NULL, &TurnLeftTask_attributes);

  /* creation of TurnRightTask */
  TurnRightTaskHandle = osThreadNew(StartTurnRightTask, NULL, &TurnRightTask_attributes);

  /* creation of ConnectionTask */
  ConnectionTaskHandle = osThreadNew(StartConnectionTask, NULL, &ConnectionTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartOLEDTask */
/**
  * @brief  Function implementing the OLEDTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartOLEDTask */
void StartOLEDTask(void *argument)
{
  /* USER CODE BEGIN StartOLEDTask */
	// Prepare bodyVersion string
	strcat(bodyVersion, versionName);

	// Initiate display
	ssd1306_Init();
	uint8_t y = 0;
	ssd1306_Fill(Black);

  /* Infinite loop */
  for(;;)
  {
	  // Set header
	  ssd1306_SetCursor(2, y);
	  ssd1306_WriteString(headerBootingUp, Font_7x10, White);
	  y += 30;

	  // Set body
	  ssd1306_SetCursor(2, y);
	  ssd1306_WriteString(bodyVersion, Font_11x18, White);
	  y += 36;

	  ssd1306_UpdateScreen();
	  y = 0;

	  vTaskSuspend(NULL);
  }
  /* USER CODE END StartOLEDTask */
}

/* USER CODE BEGIN Header_StartDispatcherTask */
/**
* @brief Function implementing the DispatcherTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDispatcherTask */
void StartDispatcherTask(void *argument)
{
  /* USER CODE BEGIN StartDispatcherTask */
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  switch(rx_buffer[0]) {
		case 0x1:		// Stop vehicle.
			vTaskResume(StopTaskHandle);
			break;
		case 0x2:		// Toggle driving lights.
			vTaskResume(DrivingLightsTaHandle);
			break;
		case 0x3:		// Toggle RGB stripe.
			vTaskResume(LEDStripeTaskHandle);
			break;
		case 0x4:		// Turn left blinkers on.
			vTaskResume(LeftBlinkersTasHandle);
			break;
		case 0x5:		// Turn right blinkers on.
			vTaskResume(RightBlinkersTaHandle);
			break;
		case 0x6:		// Toggle parking to the left.
			vTaskResume(ParkLeftTaskHandle);
			break;
		case 0x7:		// Toggle parking to the right.
			vTaskResume(ParkRightTaskHandle);
			break;
		case 0x11:		// Accelerate.
			vTaskResume(AccelerateTaskHandle);
			break;
		case 0x12:		// Decelerate.
			vTaskResume(DecelerateTaskHandle);
			break;
		case 0x13:		// Turn left.
			vTaskResume(TurnLeftTaskHandle);
			break;
		case 0x14:		// Turn right.
			vTaskResume(TurnRightTaskHandle);
			break;
		default:		// Acknowledge connection.
			vTaskResume(ConnectionTaskHandle);
		}
  }
  /* USER CODE END StartDispatcherTask */
}

/* USER CODE BEGIN Header_StartStopTask */
/**
* @brief Function implementing the StopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStopTask */
void StartStopTask(void *argument)
{
  /* USER CODE BEGIN StartStopTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartStopTask */
}

/* USER CODE BEGIN Header_StartDrivingLightsTask */
/**
* @brief Function implementing the DrivingLightsTa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDrivingLightsTask */
void StartDrivingLightsTask(void *argument)
{
  /* USER CODE BEGIN StartDrivingLightsTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDrivingLightsTask */
}

/* USER CODE BEGIN Header_StartLEDStripeTask */
/**
* @brief Function implementing the LEDStripeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLEDStripeTask */
void StartLEDStripeTask(void *argument)
{
  /* USER CODE BEGIN StartLEDStripeTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLEDStripeTask */
}

/* USER CODE BEGIN Header_StartLeftBlinkersTask */
/**
* @brief Function implementing the LeftBlinkersTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLeftBlinkersTask */
void StartLeftBlinkersTask(void *argument)
{
  /* USER CODE BEGIN StartLeftBlinkersTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLeftBlinkersTask */
}

/* USER CODE BEGIN Header_StartRightBlinkersTask */
/**
* @brief Function implementing the RightBlinkersTa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRightBlinkersTask */
void StartRightBlinkersTask(void *argument)
{
  /* USER CODE BEGIN StartRightBlinkersTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartRightBlinkersTask */
}

/* USER CODE BEGIN Header_StartParkLeftTask */
/**
* @brief Function implementing the ParkLeftTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParkLeftTask */
void StartParkLeftTask(void *argument)
{
  /* USER CODE BEGIN StartParkLeftTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartParkLeftTask */
}

/* USER CODE BEGIN Header_StartParkRightTask */
/**
* @brief Function implementing the ParkRightTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParkRightTask */
void StartParkRightTask(void *argument)
{
  /* USER CODE BEGIN StartParkRightTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartParkRightTask */
}

/* USER CODE BEGIN Header_StartAccelerateTask */
/**
* @brief Function implementing the AccelerateTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAccelerateTask */
void StartAccelerateTask(void *argument)
{
  /* USER CODE BEGIN StartAccelerateTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartAccelerateTask */
}

/* USER CODE BEGIN Header_StartDecelerateTask */
/**
* @brief Function implementing the DecelerateTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDecelerateTask */
void StartDecelerateTask(void *argument)
{
  /* USER CODE BEGIN StartDecelerateTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDecelerateTask */
}

/* USER CODE BEGIN Header_StartTurnLeftTask */
/**
* @brief Function implementing the TurnLeftTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTurnLeftTask */
void StartTurnLeftTask(void *argument)
{
  /* USER CODE BEGIN StartTurnLeftTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTurnLeftTask */
}

/* USER CODE BEGIN Header_StartTurnRightTask */
/**
* @brief Function implementing the TurnRightTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTurnRightTask */
void StartTurnRightTask(void *argument)
{
  /* USER CODE BEGIN StartTurnRightTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTurnRightTask */
}

/* USER CODE BEGIN Header_StartConnectionTask */
/**
* @brief Function implementing the ConnectionTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartConnectionTask */
void StartConnectionTask(void *argument)
{
  /* USER CODE BEGIN StartConnectionTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartConnectionTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

