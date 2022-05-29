/*
 * i2c.h
 *
 *  Created on: 29-May-2022
 *      Author: yeshasyesodharan
 */

#ifndef GLBINC_I2C_H_
#define GLBINC_I2C_H_

#include <stdint.h>

/* I2C identfiers */
#define I2C1_NUM										0U
#define I2C2_NUM										1U
#define I2C3_NUM										2U

#define I2C_OK											0U
#define I2C_NOT_OK										1U
#define NULL_PTR										((void *)0)

#define I2C_MASTER
#define I2C_SCL_SPEED_SM								100000U
#define I2C_SCL_SPEED_FM								400000U

#define I2C_ACK_EN										1U
#define I2C_ACK_DIS										0U

#define I2C_DUTY_CYCLE_2								0U
#define I2C_DUTY_CYCLE_16_9								1U
typedef struct
{
	uint32_t scl_speed;
	uint8_t	 device_address;
	uint8_t	 ack_control;
	uint8_t  duty_cycle;
}I2C_ConfigType;

uint8_t I2C_Init(uint8_t i2c_peripheral, I2C_ConfigType *config);
#endif /* GLBINC_I2C_H_ */
