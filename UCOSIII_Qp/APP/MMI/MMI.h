#ifndef _MMI_H
#define _MMI_H
#include "sys.h"
#include "oledgui.h"
#include "spi_oled.h"

void MMI_task(void *p_arg);
void show_loading(u8 count,u8 start_lin,u8 start_col);// 1 44;
void SHOW_CG(void);

#endif
