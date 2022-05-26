/*
 * gpio_gen.c
 *
 *  Created on: 23-May-2022
 *      Author: yeshasyesodharan
 */


#include "gpio.h"
#include "gpio_gen.h"
#include "gpio_drv.h"

const GPIO_IODataType GPIO_Cfg[GEN_GPIO_NUM_CONFIGURED] =
{
	{
        
                    10,				    /* GPIO Number */ 
                    {                                         
                            11,			/* GPIO Mode */   
                            12,			/* GPIO Output Type */
                            13,			/* GPIO Speed Type */
                            14,			/* GPIO PUPD Type */
                            15,			/* GPIO Alternate Function*/
                            16,			/* GPIO Interrupt Required */
                            {
                                17,
                                18
                            },
                    }
            
    }
};
