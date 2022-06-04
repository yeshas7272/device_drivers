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

static inline void I2CDrv_GenerateStopCondition(I2C_RegDefType *i2c_peripheral_regs)
{
	while(! ((i2c_peripheral_regs->I2C_SR1 & (1 << I2C_SR1_TXE_BIT_POS)) && (i2c_peripheral_regs->I2C_SR1 & (1 << I2C_SR1_BTF_BIT_POS))) );
	i2c_peripheral_regs->I2C_CR1 |= (1 << I2C_CR1_STOP_BIT_POS);
}

static inline void I2CDrv_GenerateStartCondition(I2C_RegDefType *i2c_peripheral_regs)
{
	i2c_peripheral_regs->I2C_CR1 |= (1 << I2C_CR1_START_BIT_POS);
}

static inline void I2CDrv_SendAddress(I2C_RegDefType *i2c_peripheral_regs, uint8_t slave_address)
{
	/* Slave address is 7 bit long and are stored in bits 1 to 8 of data register*/
	i2c_peripheral_regs->I2C_DR = (((slave_address & 0xFF) << 1) & (~1));
}

static inline void I2CDrv_ClearADDR(I2C_RegDefType *i2c_peripheral_regs)
{
	uint32_t sr1 = i2c_peripheral_regs->I2C_SR1;
	uint32_t sr2 = i2c_peripheral_regs->I2C_SR2;

	(void)sr1;
	(void)sr2;
}

void I2CDrv_MasterSend(I2C_RegDefType *i2c_peripheral_regs, uint8_t *buffer, uint32_t len, uint8_t slave_address)
{

	/* generate start condition indicated by SB = 0.
	 * while SB = 1 SCL will be stretched */
	I2CDrv_GenerateStartCondition(i2c_peripheral_regs);

	/* wait for start condition generation*/
	while(!(i2c_peripheral_regs->I2C_SR1 & (1 << I2C_SR1_START_BIT_POS)));

	/* Send Address of the destination */
	I2CDrv_SendAddress(i2c_peripheral_regs, slave_address);

	/* Clear ADDR flag by reading SR1 and SR2, untill it is clear SCL will be stretched */
	I2CDrv_ClearADDR(i2c_peripheral_regs);

	/* Send all data, if TXE = 1*/
	while(len > 0)
	{
		while(! (i2c_peripheral_regs->I2C_SR1 & (1 << I2C_SR1_TXE_BIT_POS) ));
		i2c_peripheral_regs->I2C_DR = *buffer;
		buffer++;
		len--;
	}

	/* Generate Stop condition if TXE = 1 and BTF = 1 */

	I2CDrv_GenerateStopCondition(i2c_peripheral_regs);
}

void I2CDrv_ConfigureSCL(I2C_RegDefType *i2c_peripheral_regs, I2C_ConfigType *config )
{
	uint32_t system_clock_freq = 0;
	uint16_t ahb_prescalar = 0;
	uint8_t apb1_prescalar = 0;
	uint32_t peripheral_clk = 0;
	uint8_t trise = 0;
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

	i2c_peripheral_regs->I2C_CR2 |= (i2c_cr2_freq & 0x3FU);

	if(config->scl_speed <= I2C_SCL_SPEED_SM)
	{
		/* Standard Mode Config */
		ccr = peripheral_clk / (2 * I2C_SCL_SPEED_SM);
		i2c_peripheral_regs->I2C_CCR |= ccr;
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
		i2c_peripheral_regs->I2C_CCR |= reg;

	}

	/* Configure TRISE */
	trise = i2c_cr2_freq + 1;
	i2c_peripheral_regs->I2C_TRISE = (trise & 0x3FU);
}
