/*
 * gpio_drv.h
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#ifndef PRV_INC_GPIO_DRV_H_
#define PRV_INC_GPIO_DRV_H_

#include <stdint.h>
/* Port A to E*/
#define GPIO_NUM_OF_PORTS				0x5U
/* GPIO 0-15*/
#define GPIO_NUM_OF_PORT_IO				0xFU

/* RCC Register to enable GPIO Clock */
#define	RCC_APB1_EN						(*(volatile uint32_t *)0x40023830U)
/*
 * GPIO Register Address Offsets
 * Refer Table 26. GPIO register map and reset values in RM0383
 *
 **/
#define GPIOx_MODER_OFFSET				0x0U
#define GPIOx_OTYPER_OFFSET				0x4U
#define GPIOx_OSPEEDR_OFFSET			0x8U
#define GPIOx_PUPDR_OFFSET				0xCU
#define GPIOx_IDR_OFFSET				0x10U
#define GPIOx_ODR_OFFSET				0x14U
#define GPIOx_BSRR_OFFSET				0x18U
#define GPIOx_LCKR_OFFSET				0x1CU
#define GPIOx_AFRL_OFFSET				0x20U
#define GPIOx_AFRH_OFFSET				0x24U

#define GPIOx_MODER_PIN_OFFSET			0x2U
#define GPIOx_OTYPER_PIN_OFFSET			0x1U
#define GPIOx_OSPEEDR_PIN_OFFSET		0x2U
#define GPIOx_PUPDR_PIN_OFFSET			0x2U
#define GPIOx_IDR_PIN_OFFSET			0x1U
#define GPIOx_0DR_PIN_OFFSET			0x1U
#define GPIOx_BSRR_PIN_OFFSET			0x1U
#define GPIOx_LCKR_PIN_OFFSET			0x1U
#define GPIOx_AFRL_PIN_OFFSET			0x4U
#define GPIOx_AFRH_PIN_OFFSET			0x4U

/*
 * GPIO Register Addresses
 * Refer Table 10. STM32F411xC/xE register boundary addresses in DS10314
 *
 **/
#define GPIOx_BASE_ADDRESS(gpio)		((volatile uint32_t *)(0x4002000U + (gpio * 0x400U)))
#define GPIOx_MODER_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_MODER_OFFSET))
#define GPIOx_OTYPER_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_OTYPER_OFFSET))
#define GPIOx_OSPEEDR_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_OSPEEDR_OFFSET))
#define GPIOx_PUPDR_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_PUPDR_OFFSET))
#define GPIOx_IDR_ADDRESS(gpio)			((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_IDR_OFFSET))
#define GPIOx_ODR_ADDRESS(gpio)			((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_ODR_OFFSET))
#define GPIOx_BSRR_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_BSRR_OFFSET))
#define GPIOx_LCKR_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_LCKR_OFFSET))
#define GPIOx_AFRL_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_AFRL_OFFSET))
#define GPIOx_AFRH_ADDRESS(gpio)		((volatile uint32_t *)(GPIOx_BASE_ADDRESS(gpio) + GPIOx_AFRH_OFFSET))

typedef void (*GPIO_IntrCbk)(void *);

typedef enum
{
	GPIO_INIT_DONE = 0,
	GPIO_NO_INIT
}GPIO_PortStateType;

typedef struct
{
	uint8_t mode : 2;
	uint8_t type : 1;
	uint8_t speed: 2;
	uint8_t pupd : 2;
	uint8_t af   : 4;
	uint8_t reserved: 5;
}GPIO_ConfigType;

typedef struct
{
	uint8_t gpio_num;
	uint8_t intr_enabled;
	GPIO_IntrCbk intr_cbk;
	GPIO_ConfigType gpio_config;
}GPIO_IODataType;

typedef struct
{
	GPIO_IODataType gpios[GPIO_NUM_OF_PORT_IO];
	uint8_t lookup[GPIO_NUM_OF_PORT_IO];
	GPIO_PortStateType state;
}GPIO_PortType;

typedef struct
{
	GPIO_PortType portData[GPIO_NUM_OF_PORTS];
}GPIO_DriverContext;


uint8_t GPIO_WriteConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig);
uint8_t GPIO_ReadConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType **eConfig);
uint8_t GPIO_ReadInput(uint8_t nGPIOPort, uint8_t nGPIONum);
uint8_t GPIO_ReadOutPut(uint8_t nGPIOPort, uint8_t nGPIONum);
#endif /* PRV_INC_GPIO_DRV_H_ */
