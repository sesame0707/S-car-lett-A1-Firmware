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
#include "ssd1306.h"
#include "ssd1306_conf_template.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"
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

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OLEDPrintTask */
osThreadId_t OLEDPrintTaskHandle;
const osThreadAttr_t OLEDPrintTask_attributes = {
  .name = "OLEDPrintTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void dashboard(char* header, char* logotype) {
	ssd1306_Init();

    uint8_t y = 0;
    ssd1306_Fill(Black);

	#ifdef SSD1306_INCLUDE_FONT_7x10
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString(header, Font_7x10, White);
    y += 30;
    #endif

    #ifdef SSD1306_INCLUDE_FONT_11x18
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString(logotype, Font_11x18, White);
    y += 36;
    #endif

    ssd1306_UpdateScreen();
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartOLEDPrintTask(void *argument);

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

  /* creation of OLEDPrintTask */
  OLEDPrintTaskHandle = osThreadNew(StartOLEDPrintTask, NULL, &OLEDPrintTask_attributes);

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
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartOLEDPrintTask */
/**
* @brief Function implementing the OLEDPrintTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOLEDPrintTask */
void StartOLEDPrintTask(void *argument)
{
  /* USER CODE BEGIN StartOLEDPrintTask */
//	ssd1306_TestAll();
	char header[] = "Connected";
	char logotype[] = "S(car)lett";

	dashboard(header, logotype);
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartOLEDPrintTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

