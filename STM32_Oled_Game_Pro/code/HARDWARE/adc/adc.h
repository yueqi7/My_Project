#ifndef _ADC_H_
#define _ADC_H_
#include "sys.h"

void  Adc_Init(void);
float Get_Adc(u8 ch);
float Check_Voltage(float V);
#endif

