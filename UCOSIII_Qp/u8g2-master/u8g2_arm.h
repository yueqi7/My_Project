#ifndef _u8g2_arm_h
#define _u8g2_arm_h
#include "stdint.h"
#include "u8g2.h"
#include "u8x8.h"
#include "spi_oled.h"

uint8_t u8x8_byte_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)   ;
uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr);

#endif 


