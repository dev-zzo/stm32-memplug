/**
  ******************************************************************************
  * @file    Templates/Src/stm32f1xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "debug.h"

/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspDeInit(void)
{
}

/**
  * @brief  Initializes the MMC MSP.
  * @param  hmmc: Pointer to MMC handle
  * @retval None
  */
void HAL_MMC_MspInit(MMC_HandleTypeDef* hsd)
{
    GPIO_InitTypeDef gpio;

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_RELEASE_RESET();
    __HAL_RCC_GPIOD_RELEASE_RESET();
    __HAL_RCC_SDIO_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    /**SDIO GPIO Configuration
    PC12    ------> SDIO_CK
    PD2     ------> SDIO_CMD
    PC7     ------> SDIO_D7 (unused)
    PC6     ------> SDIO_D6 (unused)
    PB9     ------> SDIO_D5 (unused)
    PB8     ------> SDIO_D4 (unused)
    PC11    ------> SDIO_D3
    PC10    ------> SDIO_D2
    PC9     ------> SDIO_D1
    PC8     ------> SDIO_D0
    */

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio.Pin = GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8;
    HAL_GPIO_Init(GPIOC, &gpio);

    gpio.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &gpio);
}

/**
  * @brief  Initializes the FSMC NOR MSP.
  * @param  hmmc: Pointer to NOR handle
  * @retval None
  */
void HAL_NOR_MspInit(NOR_HandleTypeDef *hnor)
{
	GPIO_InitTypeDef gpio;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOA_RELEASE_RESET();
    __HAL_RCC_GPIOD_RELEASE_RESET();
    __HAL_RCC_GPIOE_RELEASE_RESET();
    __HAL_RCC_GPIOF_RELEASE_RESET();
    __HAL_RCC_GPIOG_RELEASE_RESET();
    __HAL_RCC_AFIO_CLK_ENABLE();

    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &gpio);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pin =
         GPIO_PIN_0
        |GPIO_PIN_1
        |GPIO_PIN_4
        |GPIO_PIN_5
        |GPIO_PIN_7
        |GPIO_PIN_8
        |GPIO_PIN_9
        |GPIO_PIN_10
        |GPIO_PIN_11
        |GPIO_PIN_12
        |GPIO_PIN_13
        |GPIO_PIN_14
        |GPIO_PIN_15
        ;
    HAL_GPIO_Init(GPIOD, &gpio);

    gpio.Pin =
         GPIO_PIN_2
        |GPIO_PIN_3
        |GPIO_PIN_4
        |GPIO_PIN_5
        |GPIO_PIN_6
        |GPIO_PIN_7
        |GPIO_PIN_8
        |GPIO_PIN_9
        |GPIO_PIN_10
        |GPIO_PIN_11
        |GPIO_PIN_12
        |GPIO_PIN_13
        |GPIO_PIN_14
        |GPIO_PIN_15
        ;
    HAL_GPIO_Init(GPIOE, &gpio);

    gpio.Pin =
         GPIO_PIN_0
        |GPIO_PIN_1
        |GPIO_PIN_2
        |GPIO_PIN_3
        |GPIO_PIN_4
        |GPIO_PIN_5
        |GPIO_PIN_12
        |GPIO_PIN_13
        |GPIO_PIN_14
        |GPIO_PIN_15
        ;
    HAL_GPIO_Init(GPIOF, &gpio);

    gpio.Pin =
         GPIO_PIN_0
        |GPIO_PIN_1
        |GPIO_PIN_2
        |GPIO_PIN_3
        |GPIO_PIN_4
        |GPIO_PIN_5
        |GPIO_PIN_13
        |GPIO_PIN_14
        ;
    HAL_GPIO_Init(GPIOG, &gpio);

    gpio.Pin = GPIO_PIN_6;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &gpio);

    __HAL_RCC_FSMC_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

    DEBUG_PrintString("HAL_NOR_MspInit done\n");
}
