from gpio_cfg import *
import json

cfg_dict = {}

with open("gpio.json", "r") as cfg_file:
    cfg_dict = json.load(cfg_file)

gpio_cfg = cfg_dict["gpio"]

for key in gpio_cfg.keys():
    print(key)
    port_cfg = GPIO_PortCfg(key)
    print(port_cfg.get_port_string())
    for cfg in gpio_cfg[key]:
        print(cfg)
        if cfg["mode"] == 0:
            print("Input Mode")
        else:
            print("Output Mode")