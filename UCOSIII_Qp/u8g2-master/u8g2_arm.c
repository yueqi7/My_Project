#include "u8g2_arm.h"

extern  SPI_TypeDef* OLED_SPI;

uint8_t u8x8_byte_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)   
{  
  uint8_t *data;  

  switch(msg)   
  {  
    case U8X8_MSG_BYTE_INIT:						break;//OLED_Init(WHITE);	
    case U8X8_MSG_BYTE_START_TRANSFER:	OLED_CS=0;  			break;
		case U8X8_MSG_BYTE_SET_DC:					OLED_DC=arg_int;	break;  
		case U8X8_MSG_BYTE_SEND:  					data = (uint8_t *)arg_ptr;  
																				while( arg_int > 0 ){  
																					SPI_ReadWriteByte(OLED_SPI,(uint8_t)*data);
																					data++;  
																					arg_int--;}    
																				break;  
    case U8X8_MSG_BYTE_END_TRANSFER:    OLED_CS=1;       break;  
    default:  
      return 0;  
  }    
  return 1;  
}  

uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
	switch(msg){
		//Initialize SPI peripheral
		case U8X8_MSG_GPIO_AND_DELAY_INIT:			SPIx_Init(OLED_SPI);	OLED_Init(BLACK);
					break;
		case U8X8_MSG_DELAY_MILLI:		delay_ms(arg_int);	break;
		
		case U8X8_MSG_DELAY_10MICRO:	delay_us(arg_int);	break;
		
		case U8X8_MSG_DELAY_100NANO:	__NOP();						break;
		
		case U8X8_MSG_GPIO_CS:				OLED_CS=arg_int;		break;
		
		case U8X8_MSG_GPIO_DC:				OLED_DC=arg_int;		break;
		
		case U8X8_MSG_GPIO_RESET:   	OLED_RST=arg_int;		break;
		default:
			return 0; //A message was received which is not implemented, return 0 to indicate an error
	}
	return 1; // command processed successfully.
}

