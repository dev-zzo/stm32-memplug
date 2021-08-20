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
#include "nor_driver.h"
#include "nand_driver.h"

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
    GPIO_InitTypeDef gpio;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOA_RELEASE_RESET();

    gpio.Pin = GPIO_PIN_8;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &gpio);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void MEM_ControlRST(int state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
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
void HAL_MMC_MspInit(MMC_HandleTypeDef* hmmc)
{
    GPIO_InitTypeDef gpio;

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_RELEASE_RESET();
    __HAL_RCC_GPIOD_RELEASE_RESET();
    __HAL_RCC_SDIO_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio.Pin =
         GPIO_PIN_12    /* CLK */
        |GPIO_PIN_11    /* D3 */
        |GPIO_PIN_10    /* D2 */
        |GPIO_PIN_9     /* D1 */
        |GPIO_PIN_8     /* D0 */
        ;
    HAL_GPIO_Init(GPIOC, &gpio);

    gpio.Pin = GPIO_PIN_2;  /* CMD */
    HAL_GPIO_Init(GPIOD, &gpio);

    MEM_ControlRST(0);
}

/**
  * @brief  Initializes the FSMC NOR MSP.
  * @param  hnor: Pointer to NOR handle
  * @retval None
  */
void NOR_MspInit(NOR_Handle_t *hnor)
{
	GPIO_InitTypeDef gpio;

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_FSMC_CLK_ENABLE();

    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Mode = GPIO_MODE_AF_PP;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOD_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_0     /* D2 */
        |GPIO_PIN_1     /* D3 */
        |GPIO_PIN_4     /* nRE */
        |GPIO_PIN_5     /* nWE */
        |GPIO_PIN_7     /* CE */
        |GPIO_PIN_8     /* D13 */
        |GPIO_PIN_9     /* D14 */
        |GPIO_PIN_10    /* D15 or A-1 */
        |GPIO_PIN_11    /* A16 */
        |GPIO_PIN_12    /* A17 */
        |GPIO_PIN_13    /* A18 */
        |GPIO_PIN_14    /* D0 */
        |GPIO_PIN_15    /* D1 */
        ;
    HAL_GPIO_Init(GPIOD, &gpio);

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOE_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_2     /* A23 */
        |GPIO_PIN_3     /* A19 */
        |GPIO_PIN_4     /* A20 */
        |GPIO_PIN_5     /* A21 */
        |GPIO_PIN_6     /* A22 */
        |GPIO_PIN_7     /* D4 */
        |GPIO_PIN_8     /* D5 */
        |GPIO_PIN_9     /* D6 */
        |GPIO_PIN_10    /* D7 */
        |GPIO_PIN_11    /* D8 */
        |GPIO_PIN_12    /* D9 */
        |GPIO_PIN_13    /* D10 */
        |GPIO_PIN_14    /* D11 */
        |GPIO_PIN_15    /* D12 */
        ;
    HAL_GPIO_Init(GPIOE, &gpio);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOF_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_0     /* A0 */
        |GPIO_PIN_1     /* A1 */
        |GPIO_PIN_2     /* A2 */
        |GPIO_PIN_3     /* A3 */
        |GPIO_PIN_4     /* A4 */
        |GPIO_PIN_5     /* A5 */
        |GPIO_PIN_12    /* A6 */
        |GPIO_PIN_13    /* A7 */
        |GPIO_PIN_14    /* A8 */
        |GPIO_PIN_15    /* A9 */
        ;
    HAL_GPIO_Init(GPIOF, &gpio);

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOG_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_0     /* A10 */
        |GPIO_PIN_1     /* A11 */
        |GPIO_PIN_2     /* A12 */
        |GPIO_PIN_3     /* A13 */
        |GPIO_PIN_4     /* A14 */
        |GPIO_PIN_5     /* A15 */
        |GPIO_PIN_13    /* A24 */
        |GPIO_PIN_14    /* A25 */
        ;
    HAL_GPIO_Init(GPIOG, &gpio);

    gpio.Pin = GPIO_PIN_6;  /* R/B */
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &gpio);

    MEM_ControlRST(0);
}

/**
  * @brief  Initializes the FSMC NAND MSP.
  * @param  hnand: Pointer to NAND handle
  * @retval None
  */
void NAND_MspInit(NAND_Handle_t *hnand)
{
	GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_FSMC_CLK_ENABLE();

    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Mode = GPIO_MODE_AF_PP;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOD_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_0     /* IO2 */
        |GPIO_PIN_1     /* IO3 */
        |GPIO_PIN_4     /* nRE */
        |GPIO_PIN_5     /* nWE */
        |GPIO_PIN_7     /* CE2 */
        |GPIO_PIN_8     /* IO13 */
        |GPIO_PIN_9     /* IO14 */
        |GPIO_PIN_10    /* IO15 */
        |GPIO_PIN_11    /* CLE */
        |GPIO_PIN_12    /* ALE */
        |GPIO_PIN_14    /* IO0 */
        |GPIO_PIN_15    /* IO1 */
        ;
    HAL_GPIO_Init(GPIOD, &gpio);

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOE_RELEASE_RESET();
    gpio.Pin =
         GPIO_PIN_7     /* IO4 */
        |GPIO_PIN_8     /* IO5 */
        |GPIO_PIN_9     /* IO6 */
        |GPIO_PIN_10    /* IO7 */
        |GPIO_PIN_11    /* IO8 */
        |GPIO_PIN_12    /* IO9 */
        |GPIO_PIN_13    /* IO10 */
        |GPIO_PIN_14    /* IO11 */
        |GPIO_PIN_15    /* IO12 */
        ;
    HAL_GPIO_Init(GPIOE, &gpio);

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOG_RELEASE_RESET();
    gpio.Pin = GPIO_PIN_9;  /* CE3 */
    HAL_GPIO_Init(GPIOG, &gpio);

    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pin = GPIO_PIN_6;  /* R/B */
    HAL_GPIO_Init(GPIOD, &gpio);

    MEM_ControlRST(0);
}
