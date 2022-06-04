/*
 * gpio_intr.c
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */
#include "gpio_drv.h"
#include "gpio_intr.h"

volatile static int irqCounter = 0;

/**
 * @brief This function finds the port of the pin on which an interrupt is triggered
 *
 * @pre
 * @post
 * @param pin
 * @return
 */
static uint8_t GPIO_IntrGetPort(uint8_t pin)
{
	int port = 0xFFU;
	if(pin < GPIO_PIN_NUM_4)
	{
		port = (((*GPIO_SYSCFG_EXTICR1_REG_ADDR) >>
				(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= GPIO_PIN_NUM_4  && pin < GPIO_PIN_NUM_8)
	{
		port = (((*GPIO_SYSCFG_EXTICR2_REG_ADDR) >>
						(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= GPIO_PIN_NUM_8 && pin < GPIO_PIN_NUM_12)
	{
		port = (((*GPIO_SYSCFG_EXTICR3_REG_ADDR) >>
						(pin % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) & 0xF);
	}
	else if(pin >= GPIO_PIN_NUM_12 && pin < GPIO_PIN_NUM_15)
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
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(GPIO_PIN_NUM_0);
	/* Find the callback notification */
	GPIO_IntrCallback(port, GPIO_PIN_NUM_0);

	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << GPIO_PIN_NUM_0);
}

void GPIO_IntrHandlerEXTI1()
{
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(GPIO_PIN_NUM_1);
	/* Find the callback notification */
	GPIO_IntrCallback(port, GPIO_PIN_NUM_1);

	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << GPIO_PIN_NUM_1);
}

void GPIO_IntrHandlerEXTI2()
{
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(GPIO_PIN_NUM_2);
	/* Find the callback notification */
	GPIO_IntrCallback(port, GPIO_PIN_NUM_2);

	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << GPIO_PIN_NUM_2);
}

void GPIO_IntrHandlerEXTI3()
{
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(GPIO_PIN_NUM_3);
	/* Find the callback notification */
	GPIO_IntrCallback(port, GPIO_PIN_NUM_3);

	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << GPIO_PIN_NUM_3);
}

void GPIO_IntrHandlerEXTI4()
{
	int port = 0;
	/* Find Interrupt port */
	port = GPIO_IntrGetPort(GPIO_PIN_NUM_4);
	/* Find the callback notification */
	GPIO_IntrCallback(port, GPIO_PIN_NUM_4);
	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << GPIO_PIN_NUM_4);
}

void GPIO_IntrHandlerEXTI9_5()
{
	int i = 0;
	int port = 0;

	for( i = GPIO_PIN_NUM_5; i <= GPIO_PIN_NUM_9; i++)
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
	/* Clear Interrupt */
	*EXTI_PENDING_REG_ADDR |= (1 << i);
}
void GPIO_IntrHandlerEXTI10_15()
{
	int i = 0;
	int port = 0;
	uint32_t exti_pending_reg = *EXTI_PENDING_REG_ADDR;
	/* Find Interrupt pin */
	for( i = GPIO_PIN_NUM_10; i <= GPIO_PIN_NUM_15; i++)
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

/**
 * @brief This function performs necessary NVIC and SYSCFG configuration for a gpio interrupt
 *
 * @pre
 * @post
 * @param nGPIOPort
 * @param nGPIONum
 */
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

/**
 * @brief This function configures a gpio interrupt
 *
 * @pre
 * @post
 * @param nGPIOPort
 * @param nGPIONum
 * @param intr_config
 * @return
 */
uint8_t GPIO_WriteIntrConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_IntrConfig *intr_config)
{
	uint8_t return_value = GPIO_NOT_OK;
	if( nGPIOPort < UGPIOA ||
		nGPIOPort > UGPIOE ||
		nGPIONum < GPIO_PIN_NUM_0 ||
		nGPIONum > GPIO_PIN_NUM_15 ||
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
