gpio_port_values = {"A": "UGPIOA", "B": "UGPIOB", "C": "UGPIOC", "D": "UGPIOD", "E": "UGPIOE"}
intr_req_values = {True: 1, False: 0}
class gpio_cfg_template:
    gpio_config_template = """
    {{
        {0},									/* GPIO Port */
				{{
						{1},				    /* GPIO Number */
						{{
								{2},			/* GPIO Mode */
								{3},			/* GPIO Output Type */
								{4},			/* GPIO Speed Type */
								{5},			/* GPIO PUPD Type */
								{6},			/* GPIO Alternate Function*/
								{7},			/* GPIO Interrupt Required */
								{{
									{8},
									{9}
								}},
						}}
				}}
    }},
            """
    def __init__(self, gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk):
        self.gpio_config_template = self.gpio_config_template.format(gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk)
        
    def get_string(self):
        return self.gpio_config_template
        
class GPIO_Cfg:
    cfg = []
    cfg_str = ""
    def __init__(self, gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk):
        config = gpio_cfg_template(gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk)
        self.cfg.append(config.get_string())
        self.cfg_str = self.cfg_str.join(self.cfg)
        print(self.cfg_str)
    
    def get_cfg(self):
        return self.cfg_str
class GPIO_PortCfg:
    port_cfg_str="""const GPIO_IODataType GPIO{}_Cfg[GEN_GPIO_NUM_CONFIGURED] =
{{
        {}
}};"""
    def __init__(self, port):
        self.port_cfg_str = self.port_cfg_str.format(port)
    
    def get_port_string(self):
        return self.port_cfg_str
        
class GPIO_Gen:
    c_file_str = """/*
 * gpio_gen.c
 *
 *  Created on: 23-May-2022
 *      Author: yeshasyesodharan
 */


#include "gpio.h"
#include "gpio_gen.h"
#include "gpio_drv.h"

const GPIO_PbCfgType GPIO_Cfg[GEN_GPIO_NUM_CONFIGURED] =
{{
        {}
}};
"""
    h_file_str = """/*
 * gpio_gen.h
 *
 *  Created on: 23-May-2022
 *      Author: yeshasyesodharan
 */

#ifndef GEN_GPIO_GEN_H_
#define GEN_GPIO_GEN_H_
#include "gpio_drv.h"

#define GEN_GPIO_NUM_CONFIGURED				{}

extern GPIO_IODataType GPIO_Cfg[GEN_GPIO_NUM_CONFIGURED];
{}
#endif /* GEN_GPIO_GEN_H_ */"""
    def __init__(self, gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk):
        gpio_cfg = GPIO_Cfg(gpio_port, gpio_num, mode, otype, ospeed, pupd, af, intr_req, intr_trigger, intr_cbk)
        self.c_file_str = self.c_file_str.format(gpio_cfg.get_cfg())
        self.h_file_str = self.h_file_str.format(10, "")
    
    def write_to_file(self):
        with open("test_file.c", "w+") as f:
            f.write(self.c_file_str)
        with open("test_file.h", "w+") as f:
            f.write(self.h_file_str)

class GPIO:
    def __init__(self, gpio, gpio_cfg):
        cfg = GPIO_Gen(gpio_port_values[gpio], gpio_cfg["pin"], gpio_cfg["mode"], gpio_cfg["otype"], gpio_cfg["speed"], gpio_cfg["pupd"], gpio_cfg["af"], intr_req_values[gpio_cfg["intr"]], gpio_cfg["intr_trigger"], gpio_cfg["cbk"])
        cfg.write_to_file()
