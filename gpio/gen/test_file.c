/*
 * gpio_gen.c
 *
 *  Created on: 23-May-2022
 *      Author: yeshasyesodharan
 */


#include "gpio.h"
#include "gpio_gen.h"
#include "gpio_drv.h"

const GPIO_PbCfgType GPIO_Cfg[GEN_GPIO_NUM_CONFIGURED] =
{
        
    {
        UGPIOA,									/* GPIO Port */
				{
						3,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOA,									/* GPIO Port */
				{
						13,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOA,									/* GPIO Port */
				{
						2,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOA,									/* GPIO Port */
				{
						5,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOB,									/* GPIO Port */
				{
						3,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOB,									/* GPIO Port */
				{
						13,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOB,									/* GPIO Port */
				{
						2,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
    {
        UGPIOB,									/* GPIO Port */
				{
						5,				    /* GPIO Number */
						{
								0,			/* GPIO Mode */
								1,			/* GPIO Output Type */
								3,			/* GPIO Speed Type */
								0,			/* GPIO PUPD Type */
								0,			/* GPIO Alternate Function*/
								1,			/* GPIO Interrupt Required */
								{
									0,
									intr_cbk
								},
						}
				}
    },
            
};
