#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define GPIO_LED_PORT GPIOC
#define LED0 					PCout(1)
#define GPIO_Pin_LED0 GPIO_Pin_1

#define LED1 					PCout(0)
#define GPIO_Pin_LED1 GPIO_Pin_0


void LED_Init(void);//≥ı ºªØ
void led0_task(void *p_arg);

		 				    
#endif
