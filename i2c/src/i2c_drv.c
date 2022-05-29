/*
 * i2c_drv.c
 *
 *  Created on: May 29, 2022
 *      Author: yeshasyesodharan
 */


#include "i2c_drv.h"

static uint8_t I2C_GetAPB1PreScalar()
{
	uint8_t apb1_prescalar = 0;
	uint8_t reg_value = 0;
	static const uint16_t apb1_prescalar_values[] = {2, 4, 8, 16};

	reg_value = (((I2C_RCC_CFGR) >> I2C_RCC_CFGR_APB1_PSCLR) & 0x07U);

	if(reg_value < 4)
	{
		apb1_prescalar = 1;
	}
	else
	{
		apb1_prescalar = apb1_prescalar_values[reg_value % 4];
	}

	return apb1_prescalar;
}

static inline uint16_t I2C_GetAHB1PreScalar()
{
	uint16_t ahb_prescalar = 0;
	uint8_t reg_value = 0;
	static const uint16_t ahb_prescalar_values[] = {2, 4, 8, 16, 64, 128, 256, 512 };

	reg_value = (((I2C_RCC_CFGR) >> I2C_RCC_CFGR_AHB_PSCLR) & 0x0FU);

	if(reg_value < 8)
	{
		ahb_prescalar = 1;
	}
	else
	{
		ahb_prescalar = ahb_prescalar_values[reg_value % 8];
	}

	return ahb_prescalar;
}

static uint32_t I2C_GetSystemClkFrequency()
{
	uint32_t system_clock_freq = 0;
	uint8_t clock_source = 0;
	clock_source = ((I2C_RCC_CFGR) & I2C_RCC_CFGR_SCLK_MASK);

	if(clock_source == I2C_RCC_CFGR_SCLK_HSI)
	{
		system_clock_freq = I2C_RCC_CFGR_SCLK_HSI_FREQ;
	}
	else if(clock_source == I2C_RCC_CFGR_SCLK_HSE)
	{
		system_clock_freq = I2C_RCC_CFGR_SCLK_HSE_FREQ;
	}
	else
	{
		/* PLL */
	}

	return system_clock_freq;
}
void I2C_ConfigureSCL(uint8_t i2c_peripheral, I2C_ConfigType *config )
{
	uint32_t system_clock_freq = 0;
	uint16_t ahb_prescalar = 0;
	uint8_t apb1_prescalar = 0;
	uint32_t peripheral_clk = 0;
	uint8_t i2c_cr2_freq = 0;
	uint16_t ccr = 0;
	uint32_t reg = 0;

	system_clock_freq = I2C_GetSystemClkFrequency();
	ahb_prescalar = I2C_GetAHB1PreScalar();
	apb1_prescalar = I2C_GetAPB1PreScalar();

	/* In stm32 all i2c peripherals are connected to APB1 bus
	 * Calculate APB1 peripheral clock as
	 * apb1_clock = (system_clk / ahb_psclr) / apb1_psclr */
	peripheral_clk = ((system_clock_freq / ahb_prescalar) / apb1_prescalar);

	i2c_cr2_freq = peripheral_clk / 1000000U;

	(I2Cx_CR2_REG(i2c_peripheral)) |= (i2c_cr2_freq & 0x3FU);

	if(config->scl_speed <= I2C_SCL_SPEED_SM)
	{
		/* Standard Mode Config */
		ccr = peripheral_clk / (2 * I2C_SCL_SPEED_SM);
		(I2Cx_CCR_REG(i2c_peripheral)) |= ccr;
	}
	else
	{
		/* Fast Mode Config
		 * 1. Set Mode as Fast Mode
		 * 2. Set Duty Cycle
		 * 3. Set CCR
		 * */
		reg = (1 << I2C_CCR_MASTER_MODE_BIT_POS);
		reg |= (config->duty_cycle << I2C_CCR_DUTY_BIT_POS);
		if(config->duty_cycle == I2C_DUTY_CYCLE_2)
		{
			ccr = peripheral_clk / (3 * I2C_SCL_SPEED_SM);
		}
		else
		{
			ccr = peripheral_clk / (25 * I2C_SCL_SPEED_SM);
		}

		reg |= (ccr & 0xFFFU);
		(I2Cx_CCR_REG(i2c_peripheral)) |= reg;

	}
}
