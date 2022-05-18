/*
 * gpio.h
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#ifndef GLB_INC_GPIO_H_
#define GLB_INC_GPIO_H_

/* GPIO Driver support Port A-E, Unused Port H*/
#define GPIOA							0U
#define GPIOB							1U
#define GPIOC							2U
#define GPIOD							3U
#define GPIOE							4U

/* GPIO Return types */
#define GPIO_OK							0U
#define GPIO_NOT_OK						1U
#define NULL_PTR						((void *)0)

/* GPIO MACROs to purify values*/
#define GPIO_MODE_VALUE(mode)			(mode & 0x3U)
#define GPIO_TYPE_VALUE(type)			(type & 0x1U)
#define GPIO_SPEED_VALUE(speed)			(speed & 0x3U)
#define GPIO_PUPD_VALUE(pupd)			(pupd & 0x3U)
#define GPIO_AF_VALUE(af)				(af & 0xFU)

/* GPIO Mode Types */
#define GPIO_MODE_INPUT					0U
#define GPIO_MODE_OUPUT					1U
#define GPIO_MODE_AF					2U
#define GPIO_MODE_ANALOG				3U

/* GPIO Port Output Types */
#define GPIO_OUT_PP						0U
#define GPIO_OUT_OD						1U

/* GPIO Output Speeds */
#define GPIO_SPEED_LOW					0U
#define GPIO_SPEED_MEDIUM				1U
#define GPIO_SPEED_FAST					2U
#define GPIO_SPEED_HIGH					3U

/* GPIO PUPD Types */
#define GPIO_NO_PUPD					0U
#define GPIO_PUPD_PU					1U
#define GPIO_PUPD_PD					2U
#define GPIO_PUPD_RES					3U

/* GPIO Alternate Functions */
#define GPIO_AF_0						0U
#define GPIO_AF_1						1U
#define GPIO_AF_2						2U
#define GPIO_AF_3						3U
#define GPIO_AF_4						4U
#define GPIO_AF_5						5U
#define GPIO_AF_6						6U
#define GPIO_AF_7						7U
#define GPIO_AF_8						8U
#define GPIO_AF_9						9U
#define GPIO_AF_10						10U
#define GPIO_AF_11						11U
#define GPIO_AF_12						12U
#define GPIO_AF_13						13U
#define GPIO_AF_14						14U
#define GPIO_AF_15						15U


uint8_t uGPIO_Init(uint8_t nGPIOx);
uint8_t uGPIO_Config(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig);
#endif /* PRV_INC_GPIO_H_ */
