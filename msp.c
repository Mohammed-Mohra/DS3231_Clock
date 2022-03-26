/*
 * msp.c
 *
 *  Created on: Jan 24, 2022
 *      Author: sa
 */
#include "stm32f4xx_hal.h"


void HAL_MspInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	SCB->SHCSR |= 0x7 << 16;	//enable memory fault, bus fault and usage fault

	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}


void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	//PB6 SCL 	PB7 SDA
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	GPIO_InitTypeDef	i2c_mx;
	i2c_mx.Alternate = GPIO_AF4_I2C1;
	i2c_mx.Mode = GPIO_MODE_AF_OD;
	i2c_mx.Pull = GPIO_PULLUP;
	i2c_mx.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOB, &i2c_mx);
	i2c_mx.Pin = GPIO_PIN_7;
	HAL_GPIO_Init(GPIOB, &i2c_mx);

	// lets enbable interrupts for the peripheral
	HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
}

