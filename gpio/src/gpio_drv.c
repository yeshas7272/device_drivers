/*
 * gpio_drv.c
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#include "gpio_drv.h"
#include "gpio.h"

uint8_t GPIO_ReadOutPut(uint8_t nGPIOPort, uint8_t nGPIONum)
{
	uint8_t input = 0;

	input = ((*(GPIOx_ODR_ADDRESS(nGPIOPort))) >> (GPIOx_0DR_PIN_OFFSET * nGPIONum));
	return GPIO_OUPUT_VALUE(input);
}

uint8_t GPIO_ReadInput(uint8_t nGPIOPort, uint8_t nGPIONum)
{
	uint8_t input = 0;

	input = ((*(GPIOx_IDR_ADDRESS(nGPIOPort))) >> (GPIOx_IDR_PIN_OFFSET * nGPIONum));
	return GPIO_INPUT_VALUE(input);
}

uint8_t GPIO_ReadConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType **eConfig)
{
	uint8_t return_value = GPIO_OK;
	uint8_t mode = 0;
	uint8_t type = 0;
	uint8_t speed = 0;
	uint8_t pupd = 0;
	uint8_t alternate_function = 0;
	GPIO_ConfigType *config = *eConfig;

	mode = (*(GPIOx_MODER_ADDRESS(nGPIOPort)) >> (GPIOx_MODER_PIN_OFFSET * nGPIONum));
	type = (*(GPIOx_OTYPER_ADDRESS(nGPIOPort)) >> (GPIOx_OTYPER_PIN_OFFSET * nGPIONum));
	speed = (*(GPIOx_OSPEEDR_ADDRESS(nGPIOPort)) >> (GPIOx_OSPEEDR_PIN_OFFSET * nGPIONum));
	pupd = (*(GPIOx_PUPDR_ADDRESS(nGPIOPort)) >> (GPIOx_PUPDR_PIN_OFFSET * nGPIONum));
	if(nGPIONum > 7)
	{
		alternate_function = (*(GPIOx_AFRH_ADDRESS(nGPIOPort)) >> (GPIOx_AFRH_PIN_OFFSET * nGPIONum));
	}
	else
	{
		alternate_function = (*(GPIOx_AFRL_ADDRESS(nGPIOPort)) >> (GPIOx_AFRL_PIN_OFFSET * nGPIONum));
	}

	config->mode = GPIO_MODE_VALUE(mode);
	config->type = GPIO_TYPE_VALUE(type);
	config->pupd = GPIO_PUPD_VALUE(pupd);
	config->speed = GPIO_SPEED_VALUE(speed);
	config->af = GPIO_AF_VALUE(alternate_function);

	return return_value;

}
uint8_t GPIO_WriteConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig)
{
	uint8_t return_value = GPIO_OK;
	uint8_t mode = 0;
	uint8_t type = 0;
	uint8_t speed = 0;
	uint8_t pupd = 0;
	uint8_t alternate_function = 0;

	mode = GPIO_MODE_VALUE(eConfig->mode);
	type = GPIO_TYPE_VALUE(eConfig->type);
	speed = GPIO_SPEED_VALUE(eConfig->speed);
	pupd = GPIO_PUPD_VALUE(eConfig->pupd);
	alternate_function = GPIO_AF_VALUE(eConfig->af);

	/* Configure Mode */
	*(GPIOx_MODER_ADDRESS(nGPIOPort)) |= (mode << (GPIOx_MODER_PIN_OFFSET * nGPIONum));

	if(mode == GPIO_MODE_INPUT)
	{
		/* Configure PUPD */
		*(GPIOx_PUPDR_ADDRESS(nGPIOPort)) |= (pupd << (GPIOx_PUPDR_PIN_OFFSET * nGPIONum));

	}
	else if(mode == GPIO_MODE_OUPUT)
	{
		/* Configure Output Type */
		*(GPIOx_OTYPER_ADDRESS(nGPIOPort)) |= (type << (GPIOx_OTYPER_PIN_OFFSET * nGPIONum));

		/* Configure Output Speed */
		*(GPIOx_OSPEEDR_ADDRESS(nGPIOPort)) |= (speed << (GPIOx_OSPEEDR_PIN_OFFSET * nGPIONum));
	}
	else if(mode == GPIO_MODE_AF)
	{
		if(nGPIONum > 7)
		{
			/* Configure Alternate Function */
			*(GPIOx_AFRH_ADDRESS(nGPIOPort)) |= (alternate_function << (GPIOx_AFRH_PIN_OFFSET * nGPIONum));
		}
		else
		{
			/* Configure Alternate Function */
			*(GPIOx_AFRL_ADDRESS(nGPIOPort)) |= (alternate_function << (GPIOx_AFRL_PIN_OFFSET * nGPIONum));
		}

	}

	return return_value;
}
