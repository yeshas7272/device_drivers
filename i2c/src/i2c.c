/*
 * i2c.c
 *
 *  Created on: May 29, 2022
 *      Author: yeshasyesodharan
 */
#include "i2c_drv.h"

static I2C_DriverContextType I2C_DriverContext;

/**
 * @brief This function sends data in Master Mode
 * 		  It sets the start condition
 * 		  Executes the address phase
 * 		  Waits for ack
 * 		  Executes data transmission phase
 *
 * @pre
 * @post
 * @param i2c_peripheral
 * @param buffer
 * @param len
 * @param slave_address
 * @return
 */
uint8_t I2C_MasterSend(uint8_t i2c_peripheral, uint8_t *buffer, uint32_t len, uint8_t slave_address)
{
	uint8_t return_value = I2C_NOT_OK;
	I2C_RegDefType *i2c_peripheral_regs = NULL_PTR;

	if( i2c_peripheral > I2C3_NUM ||
		buffer == NULL_PTR	||
		len == 0 ||
		I2C_DriverContext.i2c_peripheral[i2c_peripheral].state != I2C_UNINIT
	)
	{
		return return_value;
	}

	i2c_peripheral_regs = I2C_DriverContext.i2c_peripheral[i2c_peripheral].i2c_peripheral_regs;
	return_value = I2CDrv_MasterSend(i2c_peripheral_regs, buffer, len, slave_address);

	return return_value;

}
/**
 * @brief This function initializes I2C
 *
 * @pre
 * @post
 * @param i2c_peripheral
 * @param config
 * @return
 */
uint8_t I2C_Init(uint8_t i2c_peripheral, I2C_ConfigType *config)
{
	uint8_t return_value = I2C_NOT_OK;
	I2C_RegDefType *i2c_peripheral_regs = NULL_PTR;

	if( i2c_peripheral > I2C3_NUM ||
		config == NULL_PTR	||
		I2C_DriverContext.i2c_peripheral[i2c_peripheral].state != I2C_UNINIT
	)
	{
		return return_value;
	}

	/* Enable RCC Peripheral Clock */
	I2Cx_ENABLE_PCLK(i2c_peripheral);

	i2c_peripheral_regs = I2Cx_BASE_ADDRESS(i2c_peripheral);

	/* Configure SCL */
	I2CDrv_ConfigureSCL(i2c_peripheral_regs, config);


	/* Enable ACKING */
	i2c_peripheral_regs->I2C_CR1 |= (1 << I2C_CR1_ACK_BIT_POS);

	/* Set Device Address */
	i2c_peripheral_regs->I2C_OAR1 |= ((config->device_address & 0xFF) << I2C_OAR1_ADD1_7_BIT_POS);
	/* Set 14th bit of OAR1 register as per data sheet */
	i2c_peripheral_regs->I2C_OAR1 |= (1 << 14);

	/* Enable the peripheral by writing 1 to Bit 0 of CR1 register */
	i2c_peripheral_regs->I2C_CR1 |= (1 << I2C_CR1_PE_BIT_POS);

	/* Update driver context variables */
	I2C_DriverContext.i2c_peripheral[i2c_peripheral].config = *config;
	I2C_DriverContext.i2c_peripheral[i2c_peripheral].state = I2C_INIT_DONE;
	I2C_DriverContext.i2c_peripheral[i2c_peripheral].i2c_peripheral_regs = i2c_peripheral_regs;

	return_value = I2C_OK;
	return return_value;
}
