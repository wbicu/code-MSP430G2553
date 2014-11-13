#include "EPD_COG_process.h"

const struct COG_parameters_t COG_parameters[COUNT_OF_EPD_TYPE] = {
	{
		// FOR 1.44"
		{0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0x00},
		0x03,
		(128/8),
		96,
		((((128+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.0"
		{0x00,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00},
		0x03,
		(200/8),
		96,
		((((200+96)*2)/8)+1),
		0,
		480
	},
	{
		// For 2.7"
		{0x00,0x00,0x00,0x7F,0xFF,0xFE,0x00,0x00},
		0x00,
		(264/8),
		176,
		((((264+176)*2)/8)+1),
		0,
		630
	}
};

const uint8_t   SCAN_TABLE[4] = {0xC0,0x30,0x0C,0x03};
static COG_line_data_packet_type COG_Line;
static uint8_t  *data_line_even;
static uint8_t  *data_line_odd;
static uint8_t  *data_line_scan;


/**
* \brief Initialize the EPD hardware setting
*/
void EPD_init(void) {
	EPD_display_hardware_init();
	EPD_cs_low();
	EPD_pwm_low();
	EPD_rst_low();
	EPD_discharge_low();
	EPD_border_low();
}


void COG_driver_EPDtype_select(uint8_t EPD_type_index) {
	switch(EPD_type_index) {
		case EPD_144:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_144.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_144.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_144.scan[0];
		break;
		case EPD_200:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_200.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_200.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_200.scan[0];
		break;
		case EPD_270:
		data_line_even = &COG_Line.line_data_by_size.line_data_for_270.even[0];
		data_line_odd  = &COG_Line.line_data_by_size.line_data_for_270.odd[0];
		data_line_scan = &COG_Line.line_data_by_size.line_data_for_270.scan[0];
		break;
	}
}


void EPD_power_on (void) {
	/* Initial state */
	EPD_discharge_low();
	EPD_rst_low();
	EPD_cs_low();
	epd_spi_init();
	epd_spi_attach();

	PWM_run(5); //The PWM signal starts toggling
	EPD_Vcc_turn_on(); //Vcc and Vdd >= 2.7V
	PWM_run(10);
	EPD_cs_high(); // /CS=1
	EPD_border_high(); //BORDER=1
	EPD_rst_high(); // /RESET=1
	PWM_run(5);
	EPD_rst_low(); // /RESET=0
	PWM_run(5);
	EPD_rst_high(); // /RESET=1
	PWM_run(5);
}

uint8_t EPD_initialize_driver (uint8_t EPD_type_index) {
	uint8_t SendBuffer[2];
	uint16_t k;

	for (k = 0; k <= LINE_BUFFER_DATA_SIZE; k ++) {
		COG_Line.uint8[k] = 0x00;
	}
	COG_driver_EPDtype_select(EPD_type_index);
	k = 0;
	while (EPD_IsBusy()) {
		if((k++) >= 0x0FFF) return ERROR_BUSY;
	}
	epd_spi_send (0x01, (uint8_t *)&COG_parameters[EPD_type_index].channel_select, 8);
	epd_spi_send_byte (0x06, 0xFF);
	epd_spi_send_byte (0x07, 0x9D);
	epd_spi_send_byte (0x08, 0x00);
	SendBuffer[0] = 0xD0;
	SendBuffer[1] = 0x00;
	epd_spi_send (0x09, SendBuffer, 2);
	epd_spi_send_byte (0x04,COG_parameters[EPD_type_index].voltage_level);
	PWM_run(5);
	epd_spi_send_byte(0x03, 0x01);
	epd_spi_send_byte(0x03, 0x00);
	epd_spi_send_byte (0x05, 0x01);
	PWM_run(30);

	epd_spi_send_byte (0x05, 0x03);
	delay_ms (30);

	epd_spi_send_byte(0x05, 0x0F);
	delay_ms(30);

	epd_spi_send_byte(0x02, 0x24);

	return RES_OK;
}

static void stage_handle_array(uint8_t EPD_type_index, unsigned char table []) {
	uint16_t x,y,k;
	static volatile uint8_t	temp_byte;
	start_EPD_timer();

	int tempVar = 0;
	for (; tempVar<10; tempVar++){

		for (y = 0; y < COG_parameters[EPD_type_index].vertical_size; y++) {
			epd_spi_send_byte (0x04, COG_parameters[EPD_type_index].voltage_level);

			k = COG_parameters[EPD_type_index].horizontal_size-1;
			for (x = 0; x < COG_parameters[EPD_type_index].horizontal_size; x++) {
				//temp_byte =*image_prt++;
//					if (x%2==y%2) {
//						temp_byte = 0xFF;	//BIO£Y
//					} else {
//						temp_byte = 0x00;	//CZORNY
//					}

				if (table[33]==0xFF){
					temp_byte = 0xFF;
					data_line_odd[x]     = ((temp_byte & 0x80) ? WHITE3  : BLACK3 );
					data_line_odd[x]    |= ((temp_byte & 0x20) ? WHITE2  : BLACK2 );
					data_line_odd[x]    |= ((temp_byte & 0x08) ? WHITE1  : BLACK1 );
					data_line_odd[x]    |= ((temp_byte & 0x02) ? WHITE0  : BLACK0 );

					data_line_even[k]    = ((temp_byte & 0x01) ? WHITE3  : BLACK3 );
					data_line_even[k]   |= ((temp_byte & 0x04) ? WHITE2  : BLACK2 );
					data_line_even[k]   |= ((temp_byte & 0x10) ? WHITE1  : BLACK1 );
					data_line_even[k--] |= ((temp_byte & 0x40) ? WHITE0  : BLACK0 );
				}else{
					temp_byte = table[x];
					if(y==table[33]){

						data_line_odd[x]     = ((temp_byte & 0x80) ? WHITE3  : BLACK3 );
						data_line_odd[x]    |= ((temp_byte & 0x20) ? WHITE2  : BLACK2 );
						data_line_odd[x]    |= ((temp_byte & 0x08) ? WHITE1  : BLACK1 );
						data_line_odd[x]    |= ((temp_byte & 0x02) ? WHITE0  : BLACK0 );

						data_line_even[k]    = ((temp_byte & 0x01) ? WHITE3  : BLACK3 );
						data_line_even[k]   |= ((temp_byte & 0x04) ? WHITE2  : BLACK2 );
						data_line_even[k]   |= ((temp_byte & 0x10) ? WHITE1  : BLACK1 );
						data_line_even[k--] |= ((temp_byte & 0x40) ? WHITE0  : BLACK0 );

					} else {
						data_line_odd[x]    = NOTHING;
						data_line_even[k--] = NOTHING;
					}
				}

			}
			data_line_scan[(y>>2)] = SCAN_TABLE[(y%4)];
			epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8,
				COG_parameters[EPD_type_index].data_line_size);
			epd_spi_send_byte (0x02, 0x2F);
			data_line_scan[(y>>2)]=0;
		}
	}

	stop_EPD_timer();
}


void EPD_display_from_array_prt (uint8_t EPD_type_index, unsigned char table[]) {
	stage_handle_array(EPD_type_index, table);
}

static inline void nothing_frame (uint8_t EPD_type_index) {
	uint16_t i;
	for (i = 0; i <  COG_parameters[EPD_type_index].horizontal_size; i++) {
		data_line_even[i]=NOTHING;
		data_line_odd[i]=NOTHING;
	}
	for (i = 0; i < COG_parameters[EPD_type_index].vertical_size; i++) {
		epd_spi_send_byte (0x04, COG_parameters[EPD_type_index].voltage_level);
		data_line_scan[(i>>2)]=SCAN_TABLE[(i%4)];
		epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);
		epd_spi_send_byte (0x02, 0x2F);

		data_line_scan[(i>>2)]=0;
	}
}

static inline void dummy_line(uint8_t EPD_type_index) {
	uint8_t	i;
	for (i = 0; i < (COG_parameters[EPD_type_index].vertical_size/8); i++) {
		switch(EPD_type_index) {
			case EPD_144:
				COG_Line.line_data_by_size.line_data_for_144.scan[i]=0x00;
				break;
			case EPD_200:
				COG_Line.line_data_by_size.line_data_for_200.scan[i]=0x00;
				break;
			case EPD_270:
				COG_Line.line_data_by_size.line_data_for_270.scan[i]=0x00;
				break;
		}
	}
	epd_spi_send_byte (0x04, COG_parameters[EPD_type_index].voltage_level);
	epd_spi_send (0x0A, (uint8_t *)&COG_Line.uint8, COG_parameters[EPD_type_index].data_line_size);
	epd_spi_send_byte (0x02, 0x2F);
}


uint8_t EPD_power_off (uint8_t EPD_type_index) {

	nothing_frame (EPD_type_index);
	dummy_line(EPD_type_index);
	delay_ms (25);
	EPD_border_low();
	delay_ms (200);
	EPD_border_high();
	epd_spi_send_byte (0x03, 0x01);
	epd_spi_send_byte (0x02, 0x05);
	epd_spi_send_byte (0x05, 0x0E);
	epd_spi_send_byte (0x05, 0x02);
	epd_spi_send_byte (0x04, 0x0C);
	delay_ms (120);
	epd_spi_send_byte (0x05, 0x00);
	epd_spi_send_byte (0x07, 0x0D);
	epd_spi_send_byte (0x04, 0x50);
	delay_ms (40);
	epd_spi_send_byte (0x04, 0xA0);
	delay_ms (40);
	epd_spi_send_byte (0x04, 0x00);
	EPD_rst_low ();
	epd_spi_detach ();
	EPD_cs_low ();
	EPD_Vcc_turn_off ();
	EPD_border_low();
	EPD_discharge_high ();
	delay_ms (150);
	EPD_discharge_low ();

	return RES_OK;
}
