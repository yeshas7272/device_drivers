/*
 * gpio.c
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */
#include "gpio_drv.h"
#include "gpio.h"

static GPIO_DriverContext GpioCtx_st;

uint8_t uGPIO_Config(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig)
{
	GPIO_PortType *pPortData;
	uint8_t return_value = GPIO_NOT_OK;

	/* Input Validation */
	if( nGPIOPort < 0 ||
		nGPIOPort > 4 ||
		nGPIONum < 0 ||
		nGPIONum > 15 ||
		eConfig == NULL_PTR)
	{
		return GPIO_NOT_OK;
	}

	pPortData = &GpioCtx_st.portData[nGPIOPort];
	if(pPortData->state == GPIO_INIT_DONE)
	{
		return_value = GPIO_WriteConfig(nGPIOPort, nGPIONum, eConfig);

		/* Config is successful, store the config data for future references */
		if(return_value == GPIO_OK)
		{
			pPortData->gpios[nGPIONum].gpio_config = *eConfig;
		}
	}

	return return_value;
}

uint8_t uGPIO_Init(uint8_t nGPIOx)
{
	GPIO_PortType *pPortData;
	/* Input Validation */
	if(nGPIOx < 0 || nGPIOx > 4)
	{
		return GPIO_NOT_OK;
	}

	pPortData = &GpioCtx_st.portData[nGPIOx];
	/* Check if already initialized */
	if(pPortData->state == GPIO_NO_INIT)
	{
		/* Enable Clock to requested nGPIO */
		RCC_APB1_EN = (1 << nGPIOx);

		/* Set driver state*/
		pPortData->state = GPIO_INIT_DONE;
	}

	return GPIO_OK;
}

