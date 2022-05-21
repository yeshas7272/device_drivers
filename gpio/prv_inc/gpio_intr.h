/*
 * gpio_intr.h
 *
 *  Created on: May 18, 2022
 *      Author: yeshasyesodharan
 */

#ifndef PRV_INC_GPIO_INTR_H_
#define PRV_INC_GPIO_INTR_H_

#include "gpio.h"

#define RCC_SYSCFG_BIT												(14U)
#define GPIO_SYSCFG_EXTICR_REG_BASE_ADDR							(0x40013800U)
#define GPIO_SYSCFG_EXTICR1_REG_OFFSET								(0x08U)
#define GPIO_SYSCFG_EXTICR2_REG_OFFSET								(0x0CU)
#define GPIO_SYSCFG_EXTICR3_REG_OFFSET								(0x10U)
#define GPIO_SYSCFG_EXTICR4_REG_OFFSET								(0x14U)

#define GPIO_SYSCFG_EXTICR1_REG_ADDR								((volatile uint32_t *)(GPIO_SYSCFG_EXTICR_REG_BASE_ADDR + GPIO_SYSCFG_EXTICR1_REG_OFFSET))
#define GPIO_SYSCFG_EXTICR2_REG_ADDR								((volatile uint32_t *)(GPIO_SYSCFG_EXTICR_REG_BASE_ADDR + GPIO_SYSCFG_EXTICR2_REG_OFFSET))
#define GPIO_SYSCFG_EXTICR3_REG_ADDR								((volatile uint32_t *)(GPIO_SYSCFG_EXTICR_REG_BASE_ADDR + GPIO_SYSCFG_EXTICR3_REG_OFFSET))
#define GPIO_SYSCFG_EXTICR4_REG_ADDR								((volatile uint32_t *)(GPIO_SYSCFG_EXTICR_REG_BASE_ADDR + GPIO_SYSCFG_EXTICR4_REG_OFFSET))

#define GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET							(0x04U)
#define GPIO_SYSCFG_EXTICR1_PIN_RANGE								0U
#define GPIO_SYSCFG_EXTICR2_PIN_RANGE								1U
#define GPIO_SYSCFG_EXTICR3_PIN_RANGE								2U
#define GPIO_SYSCFG_EXTICR4_PIN_RANGE								3U

#define GPIO_SYSCFG_EXTICR1_VALUE(gpio_port, gpio_num)				((gpio_port) << ((gpio_num % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET))
#define GPIO_SYSCFG_EXTICR2_VALUE(gpio_port, gpio_num)				((gpio_port) << ((gpio_num % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET))
#define GPIO_SYSCFG_EXTICR3_VALUE(gpio_port, gpio_num)				((gpio_port) << ((gpio_num % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET))
#define GPIO_SYSCFG_EXTICR4_VALUE(gpio_port, gpio_num)				((gpio_port) << ((gpio_num % GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET) * GPIO_SYSCFG_EXTICR_REG_PIN_OFFSET))

#define EXTI_REG_BASE_ADDR											(0x40013C00U)
#define EXTI_IMR_REG_OFFSET											0x0U
#define EXTI_RISE_TRIGGER_REG_OFFSET								0x08U
#define EXTI_FALL_TRIGGER_REG_OFFSET								0x0CU
#define EXTI_SW_TRIGGER_REG_OFFSET									0x10U
#define EXTI_PENDING_REG_OFFSET										0x14U

#define EXTI_IMR_REG_ADDR											((volatile uint32_t *)(EXTI_REG_BASE_ADDR + EXTI_IMR_REG_OFFSET))
#define EXTI_RISE_TRIGGER_REG_ADDR									((volatile uint32_t *)(EXTI_REG_BASE_ADDR + EXTI_RISE_TRIGGER_REG_OFFSET))
#define EXTI_FALL_TRIGGER_REG_ADDR									((volatile uint32_t *)(EXTI_REG_BASE_ADDR + EXTI_FALL_TRIGGER_REG_OFFSET))
#define EXTI_SW_TRIGGER_REG_ADDR									((volatile uint32_t *)(EXTI_REG_BASE_ADDR + EXTI_SW_TRIGGER_REG_OFFSET))
#define EXTI_PENDING_REG_ADDR										((volatile uint32_t *)(EXTI_REG_BASE_ADDR + EXTI_PENDING_REG_OFFSET))

#define EXTI_IRQ0													6U
#define EXTI_IRQ1													7U
#define EXTI_IRQ2													8U
#define EXTI_IRQ3													9U
#define EXTI_IRQ4													10U
#define EXTI_IRQ9_5													23U
#define EXTI_IRQ10_15												40U

#define EXTI_FROM_GPIO(pin)											( pin == 0 ? EXTI_IRQ0 : \
																	 (pin == 1 ? EXTI_IRQ1 : \
																	 (pin == 2 ? EXTI_IRQ2 : \
																	 (pin == 3 ? EXTI_IRQ3 : \
																	 (pin == 4 ? EXTI_IRQ4 : \
																	 ((pin >= 5 && pin <= 9) ? EXTI_IRQ9_5 : \
																	 EXTI_IRQ10_15 ))))))

#define NVIC_ISER0_ADDR												((volatile uint32_t *)0xE000E100U)
#define NVIC_ISER1_ADDR												((volatile uint32_t *)0xE000E104U)
#define NVIC_ISER2_ADDR												((volatile uint32_t *)0xE000E108U)
#define NVIC_ISER3_ADDR												((volatile uint32_t *)0xE000E10CU)
#define NVIC_ISER4_ADDR												((volatile uint32_t *)0xE000E110U)
#define NVIC_ISER5_ADDR												((volatile uint32_t *)0xE000E114U)
#define NVIC_ISER6_ADDR												((volatile uint32_t *)0xE000E118U)
#define NVIC_ISER7_ADDR												((volatile uint32_t *)0xE000E11CU)

#define NVIC_ICER0_ADDR												((volatile uint32_t *)0xE000E180U)
#define NVIC_ICER1_ADDR												((volatile uint32_t *)0xE000E184U)
#define NVIC_ICER2_ADDR												((volatile uint32_t *)0xE000E188U)
#define NVIC_ICER3_ADDR												((volatile uint32_t *)0xE000E18CU)
#define NVIC_ICER4_ADDR												((volatile uint32_t *)0xE000E190U)
#define NVIC_ICER5_ADDR												((volatile uint32_t *)0xE000E194U)
#define NVIC_ICER6_ADDR												((volatile uint32_t *)0xE000E198U)
#define NVIC_ICER7_ADDR												((volatile uint32_t *)0xE000E19CU)

#define NVIC_ISPR0_ADDR												((volatile uint32_t *)0xE000E200U)
#define NVIC_ISPR1_ADDR												((volatile uint32_t *)0xE000E204U)
#define NVIC_ISPR2_ADDR												((volatile uint32_t *)0xE000E208U)
#define NVIC_ISPR3_ADDR												((volatile uint32_t *)0xE000E20CU)
#define NVIC_ISPR4_ADDR												((volatile uint32_t *)0xE000E210U)
#define NVIC_ISPR5_ADDR												((volatile uint32_t *)0xE000E214U)
#define NVIC_ISPR6_ADDR												((volatile uint32_t *)0xE000E218U)
#define NVIC_ISPR7_ADDR												((volatile uint32_t *)0xE000E21CU)

#define NVIC_ICPR0_ADDR												((volatile uint32_t *)0xE000E280U)
#define NVIC_ICPR1_ADDR												((volatile uint32_t *)0xE000E284U)
#define NVIC_ICPR2_ADDR												((volatile uint32_t *)0xE000E288U)
#define NVIC_ICPR3_ADDR												((volatile uint32_t *)0xE000E28CU)
#define NVIC_ICPR4_ADDR												((volatile uint32_t *)0xE000E290U)
#define NVIC_ICPR5_ADDR												((volatile uint32_t *)0xE000E294U)
#define NVIC_ICPR6_ADDR												((volatile uint32_t *)0xE000E298U)
#define NVIC_ICPR7_ADDR												((volatile uint32_t *)0xE000E29CU)

#define NVIC_IPR0_ADDR												((volatile uint32_t *)0xE000E400U)
#define NVIC_IPR1_ADDR												((volatile uint32_t *)0xE000E404U)
#define NVIC_IPR2_ADDR												((volatile uint32_t *)0xE000E408U)
#define NVIC_IPR3_ADDR												((volatile uint32_t *)0xE000E40CU)
#define NVIC_IPR4_ADDR												((volatile uint32_t *)0xE000E410U)
#define NVIC_IPR5_ADDR												((volatile uint32_t *)0xE000E414U)
#define NVIC_IPR6_ADDR												((volatile uint32_t *)0xE000E418U)
#define NVIC_IPR7_ADDR												((volatile uint32_t *)0xE000E41CU)


uint8_t GPIO_WriteIntrConfig(uint8_t nGPIOPort, uint8_t nGPIONum, GPIO_IntrConfig *intr_config);
#endif /* PRV_INC_GPIO_INTR_H_ */
