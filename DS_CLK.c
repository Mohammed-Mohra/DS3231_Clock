/*
 * DS_CLK.c
 *
 *  Created on: Feb 4, 2022
 *      Author: sa
 */
#include "DS_CLK.h"

// Important Note I took in acount 24 hourse not 12 am/pm hours

extern I2C_HandleTypeDef	hi2c;


static void i2c_init();
static uint8_t bcd_to_binary(uint8_t val);
static uint8_t binary_to_bcd(uint8_t val);


static uint8_t binary_to_bcd(uint8_t val)
{
	uint8_t temp_ten;
	uint8_t temp_zero;

	if(val > 9)
	{
		temp_ten = val/10;
		temp_zero = val%10;
		val = (temp_ten<<4) | (temp_zero & 0x0F);
	}
	return val;
}

static uint8_t bcd_to_binary(uint8_t val)
{
	uint8_t temp_ten;
	uint8_t temp_zero;
	if(val>9)
	{
		temp_ten = (val>>4)*10;
		temp_zero = val & 0x0F;
		val = temp_ten + temp_zero;
	}

	return val;
}



void set_clk(clk_reg_t*  clk_obj)
{
	// Initlialize the clock by calling i2c init and send it the data u need to initialize the clock start by seconds and move on
	uint8_t sec[2];
//	sec[0] = ADDR_SEC;
	uint16_t size = 2;
	i2c_init();

	uint8_t current_time[7];

	uint8_t seconds = binary_to_bcd(clk_obj->SEC);
	uint8_t min = binary_to_bcd(clk_obj->MIN);
	uint8_t hour = binary_to_bcd(clk_obj->HOUR);
	uint8_t day = binary_to_bcd(clk_obj->DAY);
	uint8_t date = binary_to_bcd(clk_obj->DATE);
	uint8_t month = binary_to_bcd(clk_obj->MONTH);
	uint8_t year = binary_to_bcd(clk_obj->YEAR);

	sec[0] = seconds;
	//sec[0] &= ~(1<<7);
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_SEC, (uint16_t)1, sec, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);


	//sec[0] = ADDR_MIN;
	sec[0] = min;
	//sec[0] &= ~(1<<7);
	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_MIN, (uint16_t)1, sec, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);

	/*      Now Set the Hours*/
//	sec[0] = ADDR_HOUR;
	sec[0] = hour;
	sec[0] &= ~(1<<7);
	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_HOUR, (uint16_t)1, sec, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);

	/*Now set the day*/
	//sec[0] = ADDR_DAY;
	sec[0] = day;
	sec[0] &= 0x7;
	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_DAY, (uint16_t)1, sec, 1)!= HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);

	/*Now Set the Date*/
	//sec[0] = ADDR_DATE;
	sec[0] = date;
	sec[0] &= ~(3<<6);

	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_DATE, (uint16_t)1, sec, 1)!= HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);

	/*Now Set the Month*/
	//sec[0] = ADDR_MONTH;
	sec[0] = month;
	sec[0] &= ~(3<<5);
	sec[0] |= (1<<7);

	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_MONTH, (uint16_t)1, sec, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);

	/*Now Set the year*/
	//sec[0] = ADDR_YEAR;
	sec[0] = year;

	i2c_init();
	if(HAL_I2C_Mem_Write_IT(&hi2c, ADDR_DS_CLK, ADDR_YEAR, (uint16_t)1, sec, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);




}



void get_clk(clk_reg_t* clk_obj)
{

	uint8_t temp_val;
	uint8_t temp_val_arr[7];

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_SEC, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->SEC = bcd_to_binary(temp_val);

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_MIN, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->MIN = bcd_to_binary(temp_val);

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_HOUR, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->HOUR = bcd_to_binary(temp_val);

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_DAY, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->DAY = bcd_to_binary(temp_val);

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_DATE, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->DATE = bcd_to_binary(temp_val);

	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_MONTH, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->MONTH = bcd_to_binary(temp_val & ~(1<<7));
	i2c_init();
	if(HAL_I2C_Mem_Read_IT(&hi2c, ADDR_DS_CLK, ADDR_YEAR, 1, &temp_val, 1) != HAL_OK)
		Error_Handler();
	while(HAL_I2C_GetState(&hi2c) !=HAL_I2C_STATE_READY);
	clk_obj->YEAR = bcd_to_binary(temp_val);


}



static void i2c_init()
{
	hi2c.Instance = I2C1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.ClockSpeed = 	50000;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	uint32_t delay = 1;
	//hi2c.Init.OwnAddress1 =	ADDR_DS_CLK;
	//hi2c.pBuffPtr = ptxBuffer;
	//hi2c.XferSize = size;

	if(HAL_I2C_Init(&hi2c) != HAL_OK)
		Error_Handler();
	//HAL_Delay(delay);

}
