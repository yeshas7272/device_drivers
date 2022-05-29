/*
 * i2c.c
 *
 *  Created on: May 29, 2022
 *      Author: yeshasyesodharan
 */
#include "i2c_drv.h"

static I2C_DriverContextType I2C_DriverContext;

uint8_t I2C_Init(uint8_t i2c_peripheral, I2C_ConfigType *config)
{
	uint8_t return_value = I2C_NOT_OK;

	if( i2c_peripheral > I2C3_NUM ||
		config == NULL_PTR	||
		I2C_DriverContext.i2c_peripheral[i2c_peripheral].state != I2C_UNINIT
	)
	{
		return return_value;
	}

	/* Enable RCC Peripheral Clock */
	I2Cx_ENABLE_PCLK(i2c_peripheral);

	/* Configure SCL */
	I2C_ConfigureSCL(i2c_peripheral, config);


	/* Enable ACKING */
	(I2Cx_CR1_REG(i2c_peripheral)) |= (1 << I2C_CR1_ACK_BIT_POS);

	/* Set Device Address */
	(I2Cx_OAR1_REG(i2c_peripheral))|= ((config->device_address & 0xFF) << I2C_OAR1_ADD1_7_BIT_POS);
	/* Set 14th bit of OAR1 register as per data sheet */
	(I2Cx_OAR1_REG(i2c_peripheral))|= (1 << 14);

	I2C_DriverContext.i2c_peripheral[i2c_peripheral].config = *config;
	I2C_DriverContext.i2c_peripheral[i2c_peripheral].state = I2C_INIT_DONE;

	return_value = I2C_OK;
	return return_value;
}
