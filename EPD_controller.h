#ifndef 	DISPLAY_CONTROLLER_H_INCLUDED
#define 	DISPLAY_CONTROLLER_H_INCLUDED
#include	"Pervasive_Displays_small_EPD.h"

void EPD_display_init(void);
void EPD_power_init(uint8_t EPD_type_index);
void EPD_display_from_pointer(uint8_t EPD_type_index, unsigned char table[]);
#endif 	//DISPLAY_CONTROLLER_H_INCLUDED
