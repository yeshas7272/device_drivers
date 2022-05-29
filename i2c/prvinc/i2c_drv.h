/*
 * i2c_drv.h
 *
 *  Created on: 29-May-2022
 *      Author: yeshasyesodharan
 */

#ifndef PRVINC_I2C_DRV_H_
#define PRVINC_I2C_DRV_H_

#include "i2c.h"

#define MAX_I2C_SUPPORTED									3U
#define BIT_ENABLE											1U
#define BIT_DISABLE											0U

typedef struct
{
	uint32_t I2C_CR1;
	uint32_t I2C_CR2;
	uint32_t I2C_OAR1;
	uint32_t I2C_OAR2;
	uint32_t I2C_DR;
	uint32_t I2C_SR1;
	uint32_t I2C_SR2;
	uint32_t I2C_CCR;
	uint32_t I2C_TRISE;
	uint32_t I2C_FLTR;

}I2C_RegDefType;

/* I2C PClk Enable MACROS */
#define	I2C_RCC_CFGR										(*(volatile uint32_t *)0x40023808U)
#define	I2C_RCC_APB1_EN										(*(volatile uint32_t *)0x40023840U)
#define I2C_RCC_CFGR_SCLK_MASK								0x3U
#define I2C_RCC_CFGR_SCLK_HSI								0x0U
#define I2C_RCC_CFGR_SCLK_HSE								0x1U
#define I2C_RCC_CFGR_SCLK_PLL								0x2U
#define I2C_RCC_CFGR_AHB_PSCLR								0x4U
#define I2C_RCC_CFGR_APB1_PSCLR								10U
#define I2C_RCC_CFGR_SCLK_HSI_FREQ							16000000U
#define I2C_RCC_CFGR_SCLK_HSE_FREQ							8000000U
#define I2C1_RCC_CLK_EN_BIT									21U
#define I2C2_RCC_CLK_EN_BIT									22U
#define I2C3_RCC_CLK_EN_BIT									23U
#define I2C1_ENABLE_PCLK									(I2C_RCC_APB1_EN |= (1 << I2C1_RCC_CLK_EN_BIT))
#define I2C2_ENABLE_PCLK									(I2C_RCC_APB1_EN |= (1 << I2C2_RCC_CLK_EN_BIT))
#define I2C3_ENABLE_PCLK									(I2C_RCC_APB1_EN |= (1 << I2C3_RCC_CLK_EN_BIT))
#define I2Cx_ENABLE_PCLK(i2c)								(i2c == I2C1_NUM ? I2C1_ENABLE_PCLK : \
															(i2c == I2C2_NUM ? I2C2_ENABLE_PCLK : I2C3_ENABLE_PCLK))


/* I2C Base Addresses */
#define I2C1_BASE_ADDRESS									(0x40005400U)
#define I2C2_BASE_ADDRESS									(0x40005800U)
#define I2C3_BASE_ADDRESS									(0x40005C00U)

#define I2C1_REGS											(( I2C_RegDefType *) I2C1_BASE_ADDRESS)
#define I2C2_REGS											(( I2C_RegDefType *) I2C2_BASE_ADDRESS)
#define I2C3_REGS											(( I2C_RegDefType *) I2C3_BASE_ADDRESS)
#define I2Cx_BASE_ADDRESS(i2c)								(i2c == I2C1_NUM ? I2C1_REGS : \
															(i2c == I2C2_NUM ? I2C2_REGS : I2C3_REGS))

#define I2C_CR1_OFFSET										0x0U
#define I2C_CR2_OFFSET										0x4U
#define I2C_OAR1_OFFSET										0x8U
#define I2C_OAR2_OFFSET										0xCU
#define I2C_DR_OFFSET										0x10U
#define I2C_SR1_OFFSET										0x14U
#define I2C_SR2_OFFSET										0x18U
#define I2C_CCR_OFFSET										0x1CU
#define I2C_TRISE_OFFSET									0x20U
#define I2C_FLTR_OFFSET										0x24U

#define I2Cx_MUL											0x4U
#define I2Cx_CR1_REG(i2c)									(*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_CR1_OFFSET))
#define I2Cx_CR2_REG(i2c)                                   (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_CR2_OFFSET))
#define I2Cx_OAR1_REG(i2c)                                  (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_OAR1_OFFSET))
#define I2Cx_OAR2_REG(i2c)                                  (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_OAR2_OFFSET))
#define I2Cx_DR_REG(i2c)                                    (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_DR_OFFSET))
#define I2Cx_SR1_REG(i2c)                                   (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_SR1_OFFSET))
#define I2Cx_SR2_REG(i2c)                                   (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_SR2_OFFSET))
#define I2Cx_CCR_REG(i2c)                                   (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_CCR_OFFSET))
#define I2Cx_TRISE_REG(i2c)                                 (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_TRISE_OFFSET))
#define I2Cx_FLTR_REG(i2c)                                  (*(volatile uint32_t *)(I2C1_BASE_ADDRESS + (I2Cx_MUL * i2c * 0x100U) + I2C_FLTR_OFFSET))

#define I2C_CR1_PE_BIT_POS								    0U
#define I2C_CR1_BUS_MODE_BIT_POS						    1U
#define I2C_CR1_SMB_TYPE_BIT_POS						    3U
#define I2C_CR1_ENARP_BIT_POS							    4U
#define I2C_CR1_ENPEC_BIT_POS							    5U
#define I2C_CR1_ENGC_BIT_POS							    6U
#define I2C_CR1_NOSTRTCH_BIT_POS						    7U
#define I2C_CR1_START_BIT_POS							    8U
#define I2C_CR1_STOP_BIT_POS							    9U
#define I2C_CR1_ACK_BIT_POS								    10U
#define I2C_CR1_POS_BIT_POS								    11U
#define I2C_CR1_PEC_BIT_POS								    12U
#define I2C_CR1_ALERT_BIT_POS							    13U
#define I2C_CR1_SWRST_BIT_POS							    15U

#define I2C_CR2_FREQ_BIT_POS							    0U
#define I2C_CR2_ITERREN_BIT_POS							    8U
#define I2C_CR2_ITEVTEN_BIT_POS							    9U
#define I2C_CR2_ITBUFEN_BIT_POS							    10U
#define I2C_CR2_DMAEN_BIT_POS							    11U
#define I2C_CR2_LAST_BIT_POS							    12U

#define I2C_OAR1_ADD0_BIT_POS							    0U
#define I2C_OAR1_ADD1_7_BIT_POS							    1U
#define I2C_OAR1_ADD8_9_BIT_POS							    8U
#define I2C_OAR1_ADD_MODE_BIT_POS						    15U

#define I2C_OAR2_DUAL_ADD_EN_BIT_POS					    0U
#define I2C_OAR2_ADD2_BIT_POS							    1U

#define I2C_SR1_START_BIT_POS							    0U
#define I2C_SR1_ADDR_BIT_POS							    1U
#define I2C_SR1_BTF_BIT_POS								    2U
#define I2C_SR1_ADD10_BIT_POS							    3U
#define I2C_SR1_STOPF_BIT_POS							    4U
#define I2C_SR1_RXNE_BIT_POS							    6U
#define I2C_SR1_TXE_BIT_POS								    7U
#define I2C_SR1_BERR_BIT_POS							    8U
#define I2C_SR1_ARLO_BIT_POS							    9U
#define I2C_SR1_AF_BIT_POS								    10U
#define I2C_SR1_OVR_BIT_POS								    11U
#define I2C_SR1_PECERR_BIT_POS							    12U
#define I2C_SR1_TOUT_BIT_POS							    14U
#define I2C_SR1_SMB_ALERT_BIT_POS						    15U

#define I2C_SR2_MSL_MODE_BIT_POS							0U
#define I2C_SR2_BUSY_BIT_POS							    1U
#define I2C_SR2_TRA_BIT_POS								    2U
#define I2C_SR2_GENCALL_BIT_POS							    4U
#define I2C_SR2_SMBDEF_BIT_POS							    5U
#define I2C_SR2_SMBHOST_BIT_POS							    6U
#define I2C_SR2_DUALF_BIT_POS								7U
#define I2C_SR2_PEC_BIT_POS							    	8U

#define I2C_CCR_MODE_BIT_POS								0U
#define I2C_CCR_DUTY_BIT_POS							    14U
#define I2C_CCR_MASTER_MODE_BIT_POS							15U

#define I2C_TRISE_MODE_BIT_POS								0U

#define RCC_SCLK_SWITCH_STATUS_HSI							0U
#define RCC_SCLK_SWITCH_STATUS_HSE							1U
#define RCC_SCLK_SWITCH_STATUS_PLL							2U

typedef uint32_t i2c_mutex;

typedef enum
{
	I2C_UNINIT=0,
	I2C_INIT_DONE
}I2C_PeripheralStateType;

typedef struct
{
	I2C_RegDefType *i2c_peripheral_regs;
	I2C_ConfigType config;
	I2C_PeripheralStateType state;
}I2C_PeripheralType;

typedef struct
{
	I2C_PeripheralType i2c_peripheral[MAX_I2C_SUPPORTED];
	i2c_mutex mutex;
}I2C_DriverContextType;

void I2CDrv_ConfigureSCL(I2C_RegDefType *i2c_peripheral_regs, I2C_ConfigType *config );
uint8_t I2CDrv_MasterSend(I2C_RegDefType *i2c_peripheral_regs, uint8_t *buffer, uint32_t len, uint8_t slave_address);
#endif /* PRVINC_I2C_DRV_H_ */
