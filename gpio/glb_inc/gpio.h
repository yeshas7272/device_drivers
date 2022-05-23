/*
 * gpio.h
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#ifndef GLB_INC_GPIO_H_
#define GLB_INC_GPIO_H_

/* GPIO Driver support Port A-E, Unused Port H*/
#define UGPIOA							0U
#define UGPIOB							1U
#define UGPIOC							2U
#define UGPIOD							3U
#define UGPIOE							4U

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
#define GPIO_INPUT_VALUE(input)			(input & 0x1U)
#define GPIO_OUPUT_VALUE(output)		(output & 0x1U)
#define GPIO_INTR_REQ_VALUE(val)		(val & 0x1U)

/* GPIO Mode Types */
#define GPIO_MODE_IN					0U
#define GPIO_MODE_OUPUT					1U
#define GPIO_MODE_AF					2U
#define GPIO_MODE_ANLG					3U

/* GPIO Port Output Types */
#define GPIO_OUT_PP						0U
#define GPIO_OUT_OD						1U

/* GPIO Output Speeds */
#define GPIO_SPEED_L					0U
#define GPIO_SPEED_M					1U
#define GPIO_SPEED_F					2U
#define GPIO_SPEED_H					3U

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

/* GPIO NUM */
#define GPIO_PIN_NUM_0					0U
#define GPIO_PIN_NUM_1					1U
#define GPIO_PIN_NUM_2					2U
#define GPIO_PIN_NUM_3					3U
#define GPIO_PIN_NUM_4					4U
#define GPIO_PIN_NUM_5					5U
#define GPIO_PIN_NUM_6					6U
#define GPIO_PIN_NUM_7					7U
#define GPIO_PIN_NUM_8					8U
#define GPIO_PIN_NUM_9					9U
#define GPIO_PIN_NUM_10					10U
#define GPIO_PIN_NUM_11					11U
#define GPIO_PIN_NUM_12					12U
#define GPIO_PIN_NUM_13					13U
#define GPIO_PIN_NUM_14					14U
#define GPIO_PIN_NUM_15					15U


typedef void (*GPIO_IntrCbk)();
typedef enum
{
	GPIO_INTR_RISING_EDGE=0,
	GPIO_INTR_FALLING_EDGE,
	GPIO_INTR_BOTH_EDGES,
	GPIO_INTR_TRIGGER_MAX
}GPIO_IntrTriggerType;

typedef struct
{
	GPIO_IntrTriggerType trigger;
	GPIO_IntrCbk intr_cbk;
}GPIO_IntrConfig;

typedef struct
{
	uint8_t mode ;
	uint8_t type;
	uint8_t speed;
	uint8_t pupd;
	uint8_t af   ;
	uint8_t intr_required;
	GPIO_IntrConfig intr_config;
	uint8_t reserved;
}GPIO_ConfigType;

uint8_t uGPIO_Init(uint8_t nGPIOx);
uint8_t uGPIO_Config(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig);
uint8_t uGPIO_ReadOutput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t *value);
uint8_t uGPIO_ReadInput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t *value);
uint8_t uGPIO_GetConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig);
uint8_t uGPIO_WriteOutput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t value);
void GPIO_IntrCallback(uint8_t nGPIOPort, uint8_t nGPIONum);
#endif /* PRV_INC_GPIO_H_ */
