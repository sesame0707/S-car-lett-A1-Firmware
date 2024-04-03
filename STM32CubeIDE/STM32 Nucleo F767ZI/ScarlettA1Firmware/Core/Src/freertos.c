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
#include <stdio.h>

/* External libraries */
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"

#include "ws2812b.h"

/* Own headers */
#include "firmwareConfig.h"
#include "commonStrings.h"
#include "commonVariables.h"
#include "commonFunctions.h"
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
/* LED stripes */
extern SPI_HandleTypeDef hspi1;
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
/* Definitions for LEDStripesTask */
osThreadId_t LEDStripesTaskHandle;
const osThreadAttr_t LEDStripesTask_attributes = {
  .name = "LEDStripesTask",
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
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TurnRightTask */
osThreadId_t TurnRightTaskHandle;
const osThreadAttr_t TurnRightTask_attributes = {
  .name = "TurnRightTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ConnectionTask */
osThreadId_t ConnectionTaskHandle;
const osThreadAttr_t ConnectionTask_attributes = {
  .name = "ConnectionTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BrakeLightsTask */
osThreadId_t BrakeLightsTaskHandle;
const osThreadAttr_t BrakeLightsTask_attributes = {
  .name = "BrakeLightsTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for WithdrawLightsT */
osThreadId_t WithdrawLightsTHandle;
const osThreadAttr_t WithdrawLightsT_attributes = {
  .name = "WithdrawLightsT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ResumeFromStopT */
osThreadId_t ResumeFromStopTHandle;
const osThreadAttr_t ResumeFromStopT_attributes = {
  .name = "ResumeFromStopT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ConnectionTaskTimer */
osTimerId_t ConnectionTaskTimerHandle;
const osTimerAttr_t ConnectionTaskTimer_attributes = {
  .name = "ConnectionTaskTimer"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartOLEDTask(void *argument);
void StartDispatcherTask(void *argument);
void StartStopTask(void *argument);
void StartDrivingLightsTask(void *argument);
void StartLEDStripesTask(void *argument);
void StartLeftBlinkersTask(void *argument);
void StartRightBlinkersTask(void *argument);
void StartParkLeftTask(void *argument);
void StartParkRightTask(void *argument);
void StartAccelerateTask(void *argument);
void StartDecelerateTask(void *argument);
void StartTurnLeftTask(void *argument);
void StartTurnRightTask(void *argument);
void StartConnectionTask(void *argument);
void StartBrakeLightsTask(void *argument);
void StartWithdrawLightsTask(void *argument);
void StartResumeFromStopTask(void *argument);
void CallbackConnectionTaskTimer(void *argument);

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

  /* Create the timer(s) */
  /* creation of ConnectionTaskTimer */
  ConnectionTaskTimerHandle = osTimerNew(CallbackConnectionTaskTimer, osTimerOnce, NULL, &ConnectionTaskTimer_attributes);

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

  /* creation of LEDStripesTask */
  LEDStripesTaskHandle = osThreadNew(StartLEDStripesTask, NULL, &LEDStripesTask_attributes);

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

  /* creation of BrakeLightsTask */
  BrakeLightsTaskHandle = osThreadNew(StartBrakeLightsTask, NULL, &BrakeLightsTask_attributes);

  /* creation of WithdrawLightsT */
  WithdrawLightsTHandle = osThreadNew(StartWithdrawLightsTask, NULL, &WithdrawLightsT_attributes);

  /* creation of ResumeFromStopT */
  ResumeFromStopTHandle = osThreadNew(StartResumeFromStopTask, NULL, &ResumeFromStopT_attributes);

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

	// Set header
	ssd1306_SetCursor(2, y);
	ssd1306_WriteString(headerBootingUp, Font_7x10, White);
	y += 30;

	// Set body
	ssd1306_SetCursor(2, y);
	ssd1306_WriteString(bodyVersion, Font_11x18, White);
	y += 36;

	// Show content
	ssd1306_UpdateScreen();
	y = 0;

	// Delay
	osDelay(STARTUP_DURATION);

  /* Infinite loop */
  for(;;)
  {
	  // Clear screen
	  ssd1306_Fill(Black);

	  if(isConnected) {
		  // Set header
		  ssd1306_SetCursor(2, y);
		  ssd1306_WriteString(headerConnected, Font_7x10, White);
		  y += 30;

		  // Set body
		  ssd1306_SetCursor(2, y);
		  ssd1306_WriteString(bodyLogotype, Font_11x18, White);
		  y += 36;
	  } else {
		  // Set header
		  ssd1306_SetCursor(2, y);
		  ssd1306_WriteString(headerDisconnected, Font_7x10, White);
		  y += 30;

		  // Set body
		  ssd1306_SetCursor(2, y);
		  ssd1306_WriteString(bodyLogotype, Font_11x18, White);
		  y += 36;
	  }

	  // Show content
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

	  switch(RxBuffer[0]) {
		case 0x01:		// Stop vehicle.
			vTaskResume(StopTaskHandle);
			break;
		case 0x02:		// Toggle driving lights.
			vTaskResume(DrivingLightsTaHandle);
			break;
		case 0x03:		// Toggle RGB stripe.
			vTaskResume(LEDStripesTaskHandle);
			break;
		case 0x04:		// Turn left blinkers on.
			vTaskResume(LeftBlinkersTasHandle);
			break;
		case 0x05:		// Turn right blinkers on.
			vTaskResume(RightBlinkersTaHandle);
			break;
		case 0x06:		// Toggle parking to the left.
			vTaskResume(ParkLeftTaskHandle);
			break;
		case 0x07:		// Toggle parking to the right.
			vTaskResume(ParkRightTaskHandle);
			break;
		case 0x0B:		// Accelerate.
			vTaskResume(AccelerateTaskHandle);
			break;
		case 0x0C:		// Decelerate.
			vTaskResume(DecelerateTaskHandle);
			break;
		case 0x0D:		// Turn left.
			vTaskResume(TurnLeftTaskHandle);
			break;
		case 0x0E:		// Turn right.
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
	  vTaskSuspend(NULL);

	  // Stop parking if applicable
	  vTaskSuspend(ParkLeftTaskHandle);
	  vTaskSuspend(ParkRightTaskHandle);

	  // Stop BLDC motor
	  sliderAccelerateDeceleratePreviousValue = sliderAccelerateDecelerateCurrentValue;
	  sliderAccelerateDecelerateCurrentValue = 0;
	  setBLDCMotorSpeed();

	  // Set LED stripes
	  isStopped = true;
	  stripesEffect = STOP;
	  ommitToggle = true;
	  internalFunctionCall = true;
	  vTaskResume(LEDStripesTaskHandle);

	  // Home stepper motor
	  moveStepperMotorUntil(0);

	  // Reset parking state
	  isParking = false;
	  vTaskDelete(ParkLeftTaskHandle);
	  vTaskDelete(ParkRightTaskHandle);
	  ParkLeftTaskHandle = osThreadNew(StartParkLeftTask, NULL, &ParkLeftTask_attributes);
	  ParkRightTaskHandle = osThreadNew(StartParkRightTask, NULL, &ParkRightTask_attributes);

	  // Turn off all the lights
	  HAL_GPIO_WritePin(DrivingLights_GPIO_Port, DrivingLights_Pin, RESET);
	  HAL_GPIO_WritePin(BrakeLights_GPIO_Port, BrakeLights_Pin, RESET);
	  HAL_GPIO_WritePin(WithdrawLights_GPIO_Port, WithdrawLights_Pin, RESET);
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
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Driving lights effect
		  HAL_GPIO_TogglePin(DrivingLights_GPIO_Port, DrivingLights_Pin);
	  }
  }
  /* USER CODE END StartDrivingLightsTask */
}

/* USER CODE BEGIN Header_StartLEDStripesTask */
/**
* @brief Function implementing the LEDStripesTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLEDStripesTask */
void StartLEDStripesTask(void *argument)
{
  /* USER CODE BEGIN StartLEDStripesTask */
	// Set StripesEffect enum
	stripesEffect = NONE;

	// Transmit 4 empty bytes to ensure SDO is low
	uint8_t d[4] = {0};
	HAL_SPI_Transmit(&hspi1, d, 4, 100);

	// Create handle and configure
	ws2812b_handle_t hws2812b;

	hws2812b.config.packing = PACKING; // See macro above
	hws2812b.config.pulse_len_1 = WS2812B_PULSE_LEN_6b;
	hws2812b.config.pulse_len_0 = WS2812B_PULSE_LEN_2b;
	hws2812b.config.first_bit_0 = WS2812B_FIRST_BIT_0_ENABLED;
	hws2812b.config.prefix_len = PREFIX_LEN; // See macro above
	hws2812b.config.suffix_len = SUFFIX_LEN; // See macro above
	hws2812b.config.spi_bit_order = WS2812B_MSB_FIRST;

	// Create array of LEDs & set LED color
	ws2812b_led_t leds[LED_COUNT];
	struct DesiredStripesColor desiredStripesColor;
	setLEDStripesEffect(stripesEffect, &desiredStripesColor);
	for(int i = 0; i < LED_COUNT; i ++) {
	  leds[i].red = desiredStripesColor.red;
	  leds[i].green = desiredStripesColor.green;
	  leds[i].blue = desiredStripesColor.blue;
	}

	// Add LEDs and count to handle
	hws2812b.led_count = LED_COUNT;
	hws2812b.leds = leds;

	// Initialize the driver
	if(ws2812b_init(&hws2812b)) {
	  printf("Invalid ws2812b config! (%s)\r\n",ws2812b_error_msg);
	  while(1) {;}
	}

	// Create buffer
	uint8_t dma_buf[ws2812b_required_buffer_len(&hws2812b)];

	// Fill buffer
	ws2812b_fill_buffer(&hws2812b, dma_buf);

	// Transmit
	HAL_SPI_Transmit_DMA(&hspi1, dma_buf, ws2812b_required_buffer_len(&hws2812b));
	HAL_Delay(10); // 10ms delay

  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // LED stripes effect
		  if(ommitToggle == false) {
			  if(isOn == false) {
				  isOn = true;
				  stripesEffect = DEFAULT;
			  } else {
				  isOn = false;
				  stripesEffect = NONE;
			  }
		  }
		  ommitToggle = false;

		  // Update LED color
		  setLEDStripesEffect(stripesEffect, &desiredStripesColor);
		  for(int i = 0; i < LED_COUNT; i ++) {
			  leds[i].red = desiredStripesColor.red;
			  leds[i].green = desiredStripesColor.green;
			  leds[i].blue = desiredStripesColor.blue;
		  }

		  // Add LEDs to handle
		  hws2812b.leds = leds;

		  // Fill buffer
		  ws2812b_fill_buffer(&hws2812b, dma_buf);

		  // Transmit
		  HAL_SPI_Transmit_DMA(&hspi1, dma_buf, ws2812b_required_buffer_len(&hws2812b));
		  HAL_Delay(10); // 10ms delay
	  }
  }
  /* USER CODE END StartLEDStripesTask */
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
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Left blinkers effect
		  for(int i = 0; i < 6; i ++) {
			  HAL_GPIO_TogglePin(LeftBlinkers_GPIO_Port, LeftBlinkers_Pin);
			  osDelay(BLINKERS_DURATION);
		  }
	  }
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
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Right blinkers effect
		  for(int i = 0; i < 6; i ++) {
			  HAL_GPIO_TogglePin(RightBlinkers_GPIO_Port, RightBlinkers_Pin);
			  osDelay(BLINKERS_DURATION);
		  }
	  }
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
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false) {
		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Park to the left
		  isParking = true;
		  park(LEFT);
		  isParking = false;
	  }
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
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false) {
		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Park to the right
		  isParking = true;
		  park(RIGHT);
		  isParking = false;
	  }
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
	HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 0.0);
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Accelerate if possible
		  if(sliderAccelerateDecelerateCurrentValue < 4) {
			  sliderAccelerateDeceleratePreviousValue = sliderAccelerateDecelerateCurrentValue;
			  sliderAccelerateDecelerateCurrentValue ++;
		  }
		  setBLDCMotorSpeed();

		  // Set withdraw lights appropriately
		  if(sliderAccelerateDecelerateCurrentValue >= 0) {
			  isWithdrawing = false;
			  vTaskResume(WithdrawLightsTHandle);
		  }
	  }
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
	HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 0.0);
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Decelerate if possible
		  if(sliderAccelerateDecelerateCurrentValue > -2) {
			  sliderAccelerateDeceleratePreviousValue = sliderAccelerateDecelerateCurrentValue;
			  sliderAccelerateDecelerateCurrentValue --;
		  }
		  setBLDCMotorSpeed();

		  // Set withdraw lights appropriately
		  if(sliderAccelerateDecelerateCurrentValue >= 0) {
			  vTaskResume(BrakeLightsTaskHandle);
		  } else {
			  isWithdrawing = true;
			  vTaskResume(WithdrawLightsTHandle);
		  }
	  }
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
	HAL_GPIO_WritePin(StepperMotorEn_GPIO_Port, StepperMotorEn_Pin, SET);
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Turn left if possible
		  if(sliderLeftRightCurrentValue > -3) {
			  sliderLeftRightPreviousValue = sliderLeftRightCurrentValue;
			  sliderLeftRightCurrentValue --;

			  moveStepperMotor(LEFT);
		  }
	  }
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
	HAL_GPIO_WritePin(StepperMotorEn_GPIO_Port, StepperMotorEn_Pin, SET);
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Parking interrupt guard
	  if(isParking == false || internalFunctionCall == true) {
		  internalFunctionCall = false;

		  // Exit stopped state if applicable
		  if(isStopped) {
			  vTaskResume(ResumeFromStopTHandle);
		  }

		  // Turn right if possible
		  if(sliderLeftRightCurrentValue < 3) {
			  sliderLeftRightPreviousValue = sliderLeftRightCurrentValue;
			  sliderLeftRightCurrentValue ++;

			  moveStepperMotor(RIGHT);
		  }
	  }
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
	  vTaskSuspend(NULL);

	  // Refresh connection state
	  osTimerStart(ConnectionTaskTimerHandle, (ACKNOWLEDGE_PACKETS_FREQUENCY + TIME_MARGIN));
	  isConnected = true;
	  vTaskResume(OLEDTaskHandle);
  }
  /* USER CODE END StartConnectionTask */
}

/* USER CODE BEGIN Header_StartBrakeLightsTask */
/**
* @brief Function implementing the BrakeLightsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBrakeLightsTask */
void StartBrakeLightsTask(void *argument)
{
  /* USER CODE BEGIN StartBrakeLightsTask */
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Brake lights effect
	  HAL_GPIO_TogglePin(BrakeLights_GPIO_Port, BrakeLights_Pin);
	  osDelay(BRAKE_LIGHTS_DURATION);
	  HAL_GPIO_TogglePin(BrakeLights_GPIO_Port, BrakeLights_Pin);
  }
  /* USER CODE END StartBrakeLightsTask */
}

/* USER CODE BEGIN Header_StartWithdrawLightsTask */
/**
* @brief Function implementing the WithdrawLightsT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartWithdrawLightsTask */
void StartWithdrawLightsTask(void *argument)
{
  /* USER CODE BEGIN StartWithdrawLightsTask */
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Withdraw lights effect
	  if(isWithdrawing) {
		  HAL_GPIO_WritePin(WithdrawLights_GPIO_Port, WithdrawLights_Pin, SET);
	  } else {
		  HAL_GPIO_WritePin(WithdrawLights_GPIO_Port, WithdrawLights_Pin, RESET);
	  }
  }
  /* USER CODE END StartWithdrawLightsTask */
}

/* USER CODE BEGIN Header_StartResumeFromStopTask */
/**
* @brief Function implementing the ResumeFromStopT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartResumeFromStopTask */
void StartResumeFromStopTask(void *argument)
{
  /* USER CODE BEGIN StartResumeFromStopTask */
  /* Infinite loop */
  for(;;)
  {
	  vTaskSuspend(NULL);

	  // Turn off LED stripes' stop effect if present
	  if(isStopped) {
		  isStopped = false;
		  if(isOn) {
			  stripesEffect = DEFAULT;
		  } else {
			  stripesEffect = NONE;
		  }
		  ommitToggle = true;
		  vTaskResume(LEDStripesTaskHandle);
	  }
  }
  /* USER CODE END StartResumeFromStopTask */
}

/* CallbackConnectionTaskTimer function */
void CallbackConnectionTaskTimer(void *argument)
{
  /* USER CODE BEGIN CallbackConnectionTaskTimer */
	vTaskResume(StopTaskHandle);
	isConnected = false;
	vTaskResume(OLEDTaskHandle);
  /* USER CODE END CallbackConnectionTaskTimer */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

