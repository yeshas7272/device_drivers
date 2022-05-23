/*
 * gpio.c
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */
#include "gpio_drv.h"
#include "gpio.h"

static GPIO_DriverContext GpioCtx_st;

static void addToLUT(uint8_t nGPIONum, GPIO_PortType **portData)
{
	GPIO_PortType *pPortData = *portData;
	int i = 0;
	for(i = 0; i < GPIO_NUM_OF_PORT_IO; i++)
	{
		if(pPortData->intrLUT[i] == 0xFF)
		{
			pPortData->intrLUT[i] = nGPIONum;
			break;
		}
	}
}
static uint8_t GPIO_ValidateInput(uint8_t nGPIOPort, uint8_t nGPIONum)
{
	if( nGPIOPort < UGPIOA ||
		nGPIOPort > UGPIOE ||
		nGPIONum < GPIO_PIN_NUM_0 ||
		nGPIONum > GPIO_PIN_NUM_15 )
	{
		return GPIO_NOT_OK;
	}

	return GPIO_OK;
}

void GPIO_IntrCallback(uint8_t nGPIOPort, uint8_t nGPIONum)
{
	GPIO_PortType *pPortData = &GpioCtx_st.portData[nGPIOPort];

	if(pPortData->gpios[nGPIONum].gpio_config.intr_required)
	{
		pPortData->gpios[nGPIONum].gpio_config.intr_config.intr_cbk();
	}
}

uint8_t uGPIO_WriteOutput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t value)
{
	uint8_t return_value = GPIO_OK;

	/* Input Validation */
	if( GPIO_OK != GPIO_ValidateInput(nGPIOPort, nGPIONum) || value < 0 || value > 1)
	{
		return GPIO_NOT_OK;
	}

	GPIO_WriteOutPut(nGPIOPort, nGPIONum, value);

	return return_value;
}

uint8_t uGPIO_ReadOutput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t *value)
{
	uint8_t return_value = GPIO_NOT_OK;

	/* Input Validation */
	if( GPIO_OK != GPIO_ValidateInput(nGPIOPort, nGPIONum) )
	{
		return GPIO_NOT_OK;
	}

	*value = GPIO_ReadOutPut(nGPIOPort, nGPIONum);

	return return_value;
}

uint8_t uGPIO_ReadInput(uint8_t nGPIOPort, uint8_t nGPIONum, uint8_t *value)
{
	uint8_t return_value = GPIO_NOT_OK;

	/* Input Validation */
	if(  GPIO_OK != GPIO_ValidateInput(nGPIOPort, nGPIONum) )
	{
		return GPIO_NOT_OK;
	}

	*value = GPIO_ReadInput(nGPIOPort, nGPIONum);

	return return_value;
}

uint8_t uGPIO_GetConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig)
{
	GPIO_PortType *pPortData;
	uint8_t return_value = GPIO_NOT_OK;

	/* Input Validation */
	if(  GPIO_OK != GPIO_ValidateInput(nGPIOPort, nGPIONum) || eConfig == NULL_PTR)
	{
		return GPIO_NOT_OK;
	}

	pPortData = &GpioCtx_st.portData[nGPIOPort];
	if(pPortData->state == GPIO_INIT_DONE)
	{
		return_value = GPIO_ReadConfig(nGPIOPort, nGPIONum, &eConfig);
	}

	return return_value;
}
uint8_t uGPIO_Config(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_ConfigType *eConfig)
{
	GPIO_PortType *pPortData;
	uint8_t return_value = GPIO_NOT_OK;

	/* Input Validation */
	if(  GPIO_OK != GPIO_ValidateInput(nGPIOPort, nGPIONum) || eConfig == NULL_PTR)
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
			pPortData->gpios[nGPIONum].gpio_num = nGPIONum;
			pPortData->gpios[nGPIONum].gpio_config = *eConfig;
			if(pPortData->gpios[nGPIONum].gpio_config.intr_required)
			{
				addToLUT(nGPIONum, &pPortData);
			}
		}
	}

	return return_value;
}

uint8_t uGPIO_Init(uint8_t nGPIOx)
{
	GPIO_PortType *pPortData;
	int i = 0;
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
		RCC_APB1_EN |= (1 << nGPIOx);
		while(!(RCC_APB1_EN & (1 << nGPIOx)));

		/* Set driver state*/
		pPortData->state = GPIO_INIT_DONE;
	}

	for(i = 0; i < GPIO_NUM_OF_PORT_IO; i++)
	{
		pPortData->intrLUT[i] = 0xFF;
	}

	return GPIO_OK;
}

