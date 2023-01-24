#pragma once

#include <stdint.h>

uint16_t get_battery_mv(void);
uint8_t get_battery_level(uint16_t battery_mv);
uint16_t get_temperature_c(void);
