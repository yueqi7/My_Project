#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define RCC_APB2Periph_LED RCC_APB2Periph_GPIOC
#define GPIO_LED GPIOC
#define Pin_LED GPIO_Pin_1
#define LED PCout(1)
typedef enum
{
    LED_ON,//=0
    LED_OFF//1
} LED_STATE;

void LED_Init(void);
//void LED_FLASH(uint8_t time);
#endif
