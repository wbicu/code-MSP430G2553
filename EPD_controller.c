#include  "EPD_controller.h"

void EPD_display_init(void) {
	EPD_init();
}


void EPD_display_from_pointer(uint8_t EPD_type_index, unsigned char table[]) {
	EPD_init();
	EPD_power_on();
	EPD_initialize_driver(EPD_type_index);
	EPD_display_from_array_prt(EPD_type_index, table);
	EPD_power_off (EPD_type_index);
}

void EPD_power_init(uint8_t EPD_type_index) {
	EPD_init();
	EPD_power_on ();
	EPD_initialize_driver (EPD_type_index);
}

