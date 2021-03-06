/*
 * gpio_drv.h
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#ifndef PRV_INC_GPIO_DRV_H_
#define PRV_INC_GPIO_DRV_H_

#include <stdint.h>
#include "gpio.h"

/* Port A to E*/
#define GPIO_NUM_OF_PORTS				0x5U
/* GPIO 0-15*/
#define GPIO_NUM_OF_PORT_IO				0xFU

/* RCC Register to enable GPIO Clock */
#define	RCC_APB1_EN						(*(volatile uint32_t *)0x40023830U)
#define	RCC_APB2_EN						(*(volatile uint32_t *)0x40023844U)
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
#define GPIOx_BASE_ADDRESS(gpio)		((0x40020000U + (gpio * 0x400U)))
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

typedef uint32_t gpio_mutex;
typedef enum
{
	GPIO_NO_INIT=0,
	GPIO_INIT_DONE,
}GPIO_PortStateType;

typedef struct
{
	uint8_t gpio_num;
	GPIO_ConfigType gpio_config;
}GPIO_IODataType;

typedef struct
{
	GPIO_IODataType gpios[GPIO_NUM_OF_PORT_IO];
	uint8_t intrLUT[GPIO_NUM_OF_PORT_IO];
	GPIO_PortStateType state;
}GPIO_PortType;

typedef struct
{
	GPIO_PortType portData[GPIO_NUM_OF_PORTS];
	gpio_mutex mutex;
}GPIO_DriverContext;


uint8_t GPIO_WriteConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig);
uint8_t GPIO_ReadConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType **eConfig);
uint8_t GPIO_ReadInput(uint8_t nGPIOPort, uint8_t nGPIONum);
uint8_t GPIO_ReadOutPut(uint8_t nGPIOPort, uint8_t nGPIONum);
void GPIO_WriteOutPut(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t value);
void mutex_init(void * mutex);
extern void unlock_mutex(void * mutex);
extern void lock_mutex(void * mutex);
#endif /* PRV_INC_GPIO_DRV_H_ */
