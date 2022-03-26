/*
 * it.c
 *
 *  Created on: Jan 24, 2022
 *      Author: sa
 */
#include	"main.h"
extern I2C_HandleTypeDef	hi2c;

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void I2C1_EV_IRQHandler()
{
	HAL_I2C_EV_IRQHandler(&hi2c);

}

void I2C1_ER_IRQHandler()
{
	HAL_I2C_ER_IRQHandler(&hi2c);

}
