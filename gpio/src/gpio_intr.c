/*
 * gpio_intr.c
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */
#include "gpio_drv.h"
#include "gpio_intr.h"

volatile static int irqCounter = 0;

static uint8_t GPIO_IntrGetPort(uint8_t pin)
{
	int port = 0xFFU;
	int i = 0;
	if(pin < 4)
	{
		port = (((*GPIO_SYSCFG_EXTICR1_REG_ADDR) >>
				(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= 4 && pin < 8)
	{
		port = (((*GPIO_SYSCFG_EXTICR2_REG_ADDR) >>
						(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= 8 && pin < 12)
	{
		port = (((*GPIO_SYSCFG_EXTICR3_REG_ADDR) >>
						(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= 12 && pin < 15)
	{
		port = (((*GPIO_SYSCFG_EXTICR3_REG_ADDR) >>
						(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else
	{

	}
	return port;
}

void GPIO_IntrHandlerEXTI0()
{
	int i = 0;
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(0);
	/* Find the callback notification */

	/* Clear Interrupt */
}

void GPIO_IntrHandlerEXTI1()
{
	int i = 0;
	uint32_t value = 0;
	/* Find Interrupt port */
	value = ((*GPIO_SYSCFG_EXTICR1_REG_ADDR) >>
			(1 % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET);
	/* Find the callback notification */

	/* Clear Interrupt */
}

void GPIO_IntrHandlerEXTI2()
{
	int i = 0;

	/* Find Interrupt pin */
	/* Find the callback notification */

	/* Clear Interrupt */
}

void GPIO_IntrHandlerEXTI3()
{
	int i = 0;

	/* Find Interrupt pin */
	/* Find the callback notification */

	/* Clear Interrupt */
}

void GPIO_IntrHandlerEXTI4()
{
	int i = 0;

	/* Find Interrupt pin */
	/* Find the callback notification */

	/* Clear Interrupt */
}

void GPIO_IntrHandlerEXTI9_5()
{
	int i = 0;
	int port = 0;

	for( i = 5; i <= 9; i++)
	{
		if(((*EXTI_PENDING_REG_ADDR) & i) >> i)
		{
			break;
		}
	}
	port = GPIO_IntrGetPort(i);

	if(port == 0xFF)
	{
		return;
	}

	/* Find the callback notification */
	GPIO_IntrCallback(port, i);
}
void GPIO_IntrHandlerEXTI10_15()
{
	int i = 0;
	int port = 0;
	uint32_t exti_pending_reg = *EXTI_PENDING_REG_ADDR;
	/* Find Interrupt pin */
	for( i = 10; i <= 15; i++)
	{
		if(((exti_pending_reg >> i) & 1) == 1)
		{
			break;
		}
	}
	port = GPIO_IntrGetPort(i);

	if(port == 0xFF)
	{
		return;
	}

	/* Find the callback notification */
	GPIO_IntrCallback(port, i);
	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << i);
}

/* Additional config register outside of GPIO driver */
static void GPIO_IntrAdditional(uint8_t nGPIOPort, uint8_t nGPIONum)
{
	uint8_t temp = 0;
	uint8_t extiLine = 0;
	/* Enable Interrupt at NVIC */
	extiLine = EXTI_FROM_GPIO(nGPIONum);

	if(extiLine <= 31)
	{
		(*NVIC_ISER0_ADDR) |= (1 << extiLine);
	}
	else
	{
		(*NVIC_ISER1_ADDR) |= (1 << (extiLine % 32));
	}

	/* Enable Peripheral Clock to SYSCFG */
	RCC_APB2_EN |= (1 << RCC_SYSCFG_BIT);

	temp = nGPIONum / 4;
	/* Enable EXTI Line */
	switch(temp)
	{
		case GPIO_SYSCFG_EXTICR1_PIN_RANGE:
			*GPIO_SYSCFG_EXTICR1_REG_ADDR |= GPIO_SYSCFG_EXTICR1_VALUE(nGPIOPort, nGPIONum);
			break;

		case GPIO_SYSCFG_EXTICR2_PIN_RANGE:
			*GPIO_SYSCFG_EXTICR2_REG_ADDR |= GPIO_SYSCFG_EXTICR2_VALUE(nGPIOPort, nGPIONum);
			break;

		case GPIO_SYSCFG_EXTICR3_PIN_RANGE:
			*GPIO_SYSCFG_EXTICR3_REG_ADDR |= GPIO_SYSCFG_EXTICR3_VALUE(nGPIOPort, nGPIONum);
			break;

		case GPIO_SYSCFG_EXTICR4_PIN_RANGE:
			*GPIO_SYSCFG_EXTICR4_REG_ADDR |= GPIO_SYSCFG_EXTICR4_VALUE(nGPIOPort, nGPIONum);
			break;

		default:
			break;
	}
}

uint8_t GPIO_WriteIntrConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_IntrConfig *intr_config)
{
	uint8_t return_value = GPIO_NOT_OK;
	if( nGPIOPort < 0 ||
		nGPIOPort > 4 ||
		nGPIONum < 0 ||
		nGPIONum > 15 ||
		intr_config->intr_cbk == NULL_PTR)
	{
		return GPIO_NOT_OK;
	}

	/* Set trigger type  */
	if(intr_config->trigger == GPIO_INTR_RISING_EDGE)
	{
		*EXTI_RISE_TRIGGER_REG_ADDR |= (1 << nGPIONum);
	}
	else if(intr_config->trigger == GPIO_INTR_FALLING_EDGE)
	{
		*EXTI_FALL_TRIGGER_REG_ADDR |= (1 << nGPIONum);
	}
	else if(intr_config->trigger == GPIO_INTR_BOTH_EDGES)
	{
		*EXTI_FALL_TRIGGER_REG_ADDR |= (1 << nGPIONum);
		*EXTI_RISE_TRIGGER_REG_ADDR |= (1 << nGPIONum);
	}
	else
	{
		return return_value;
	}

	GPIO_IntrAdditional(nGPIOPort, nGPIONum);
	/* Un mask Interrupt */
	*EXTI_IMR_REG_ADDR |= (1 << nGPIONum);

	return_value = GPIO_OK;

	return return_value;
}
