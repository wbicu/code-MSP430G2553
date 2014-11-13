#include "EPD_hardware_gpio.h"

void EPD_cs_high (void) {
	set_gpio_high(EPD_CS_PORT,EPD_CS_PIN);
}

void EPD_cs_low (void) {
	set_gpio_low(EPD_CS_PORT,EPD_CS_PIN);
}

void EPD_flash_cs_high(void) {
	set_gpio_high(Flash_CS_PORT,Flash_CS_PIN);
}

void EPD_flash_cs_low (void) {
	set_gpio_low(Flash_CS_PORT,Flash_CS_PIN);
}

void EPD_rst_high (void) {
	set_gpio_high(EPD_RST_PORT,EPD_RST_PIN);
}

void EPD_rst_low (void) {
	set_gpio_low(EPD_RST_PORT,EPD_RST_PIN);
}

void EPD_discharge_high (void) {
	set_gpio_high(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
}

void EPD_discharge_low (void) {
	set_gpio_low(EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
}

void EPD_Vcc_turn_on (void) {
	set_gpio_high(EPD_PANELON_PORT,EPD_PANELON_PIN);
}

void EPD_Vcc_turn_off (void) {
	set_gpio_low(EPD_PANELON_PORT,EPD_PANELON_PIN);
}

void EPD_border_high(void) {
	set_gpio_high(EPD_PANELON_PORT,EPD_BORDER_PIN);
}


void EPD_border_low (void) {
	set_gpio_low(EPD_PANELON_PORT,EPD_BORDER_PIN);
}

void EPD_pwm_high(void) {
	set_gpio_high(PWM_PORT,PWM_PIN);
}

void EPD_pwm_low (void) {
    config_gpio_dir_o(SPIMISO_PORT,SPIMISO_PIN);
	set_gpio_low(PWM_PORT,PWM_PIN);
}

void SPIMISO_low(void) {
	config_gpio_dir_o(SPIMISO_PORT,SPIMISO_PIN);
	set_gpio_low(SPIMISO_PORT,SPIMISO_PIN);
}

void SPIMOSI_low(void) {
	set_gpio_low(SPIMOSI_PORT,SPIMOSI_PIN);
}

void SPICLK_low(void) {
	set_gpio_low(SPICLK_PORT,SPICLK_PIN);
}

bool EPD_IsBusy(void) {
	return (bool)input_get(EPD_BUSY_PORT,EPD_BUSY_PIN);
}

void EPD_initialize_gpio(void) {
	config_gpio_dir_i( EPD_BUSY_PORT,EPD_BUSY_PIN);
	BITCLR (CS_PORT_SEL, EPD_CS_PIN);
	BITCLR (CS_PORT_SEL2,EPD_CS_PIN);
    BITCLR (Flash_CS_PORT_SEL, Flash_CS_PIN);
	BITCLR (Flash_CS_PORT_SEL2,Flash_CS_PIN);
    
	config_gpio_dir_o( EPD_CS_PORT,EPD_CS_PIN);
	config_gpio_dir_o( EPD_RST_PORT,EPD_RST_PIN);
	config_gpio_dir_o( EPD_PANELON_PORT,EPD_PANELON_PIN);
	config_gpio_dir_o( EPD_DISCHARGE_PORT,EPD_DISCHARGE_PIN);
	config_gpio_dir_o( EPD_BORDER_PORT,EPD_BORDER_PIN);
	config_gpio_dir_o( Flash_CS_PORT,Flash_CS_PIN);
    config_gpio_dir_o( PWM_PORT,PWM_PIN);
	config_gpio_dir_i( Temper_PORT,Temper_PIN);
	EPD_flash_cs_high();
	EPD_border_low();
}


