from gpio_cfg import *
import json

cfg_dict = {}

with open("gpio.json", "r") as cfg_file:
    cfg_dict = json.load(cfg_file)

gpio_cfg = cfg_dict["gpio"]

for key in gpio_cfg.keys():
    print(gpio_cfg[key])
    for cfg in gpio_cfg[key]:
        print(cfg)
        port_cfg = GPIO(key, cfg)