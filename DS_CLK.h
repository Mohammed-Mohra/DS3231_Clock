/*
 * DS_CLK.h
 *
 *  Created on: Feb 4, 2022
 *      Author: sa
 */

#ifndef INC_DS_CLK_H_
#define INC_DS_CLK_H_

#include "stm32f4xx_hal.h"
#include "main.h"

#define ADDR_DS_CLK		0xD0
#define ADDR_SEC		0x00
#define ADDR_MIN		0x01
#define ADDR_HOUR		0x02
#define ADDR_DAY		0x03
#define ADDR_DATE		0x04
#define ADDR_MONTH		0x05
#define ADDR_YEAR		0x06


#define MONDAY			1
#define TUESDAY			2
#define WEDNESDAY		3
#define THIRSDAY		4
#define FRIDAY			5
#define SATURDAY		6
#define SUNDAY			7


typedef struct {

	uint8_t SEC;
	uint8_t MIN;
	uint8_t HOUR;
	uint8_t DAY;
	uint8_t DATE;
	uint8_t MONTH;
	uint8_t YEAR;

}clk_reg_t;



uint8_t init_clk(clk_reg_t*);
void set_clk(clk_reg_t*);
void get_clk(clk_reg_t* clk_obj);


#endif /* INC_DS_CLK_H_ */
