#include <math.h>
#include "EPD_hardware_driver.h"

static  uint16_t EPD_Counter;
static uint8_t spi_flag = FALSE;

static void initialize_EPD_timer(void) {

	TA0CCTL2 &= ~(CCIFG | CCIE);
	TA0CTL = TASSEL_2 + MC_0 + TACLR + ID_3;
	TA0CCTL2 = OUTMOD_4;
	EPD_Counter = 0;
}


void start_EPD_timer(void) {
	initialize_EPD_timer();
	TA0R = 0;
	TA0CCR0 = 990 * 2; // 1ms
	TA0CCTL2 |= CCIE;
	TA0CTL |= MC_1;
	EPD_Counter = 0;
}


void stop_EPD_timer(void) {
	TA0CCTL2 &= ~CCIE;
	TA0CTL &= ~MC_1;
}


uint32_t get_current_time_tick(void) {
	return EPD_Counter;
}

void set_current_time_tick(uint32_t count) {
     EPD_Counter=count;
}

void SysTick_Handler(void) {
	EPD_Counter++;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A0(void) {
	switch (__even_in_range(TA0IV, 10)) {
	case 2:
		break;

	case 4:
		EPD_Counter++;
		LPM3_EXIT;
		break;
	}

}

void delay_ms(unsigned int ms) {
	while (ms--) {
		__delay_cycles(SMCLK_FREQ / 1000);
	}
}


void sys_delay_ms(unsigned int ms) {
	delay_ms(ms);
}

static void Wait_10us(void) {
	__delay_cycles(SMCLK_FREQ / 100000);
}


void PWM_start_toggle(void) {

}


void PWM_stop_toggle(void) {

}

void PWM_run(uint16_t ms) {
	start_EPD_timer();
	do {
		EPD_pwm_high();
		__delay_cycles(30);
		EPD_pwm_low();
		__delay_cycles(30);
	} while (get_current_time_tick() < ms);
	stop_EPD_timer();
}


void epd_spi_init(void) {
	if (spi_flag)
		return;
	spi_flag = TRUE;
	config_gpio_dir_o(SPICLK_PORT, SPICLK_PIN);
	config_gpio_dir_o(SPIMOSI_PORT, SPIMOSI_PIN);
	config_gpio_dir_i(SPIMISO_PORT, SPIMISO_PIN);

	BITSET(SPISEL, SPICLK_PIN + SPIMOSI_PIN + SPIMISO_PIN);
	BITSET(SPISEL2, SPICLK_PIN + SPIMOSI_PIN + SPIMISO_PIN);
	SPICTL0 = UCCKPH | UCMST | UCSYNC | UCMSB;
	SPICTL1 = UCSSEL_2 + UCSWRST;
	SPIBR0 = 2;
	SPIBR1 = 0;

	BITSET(REN (SPIMISO_PORT), SPIMISO_PIN);
	BITCLR(SPICTL1, UCSWRST);
}

void epd_spi_attach(void) {
	EPD_flash_cs_high();
	EPD_cs_high();
	epd_spi_init();
}

void epd_spi_detach(void) {
	BITCLR(SPISEL, SPICLK_PIN + SPIMOSI_PIN + SPIMISO_PIN);
	BITCLR(SPISEL2, SPICLK_PIN + SPIMOSI_PIN + SPIMISO_PIN);
	SPIMISO_low();
	SPIMOSI_low();
	SPICLK_low();
	spi_flag = FALSE;
}

void epd_spi_write(unsigned char Data) {
	SPITXBUF = Data;
	while (!(SPIIFG & SPITXIFG))
		;
}

void epd_spi_send (unsigned char register_index, unsigned char *register_data,
               unsigned length) {
	EPD_cs_low ();
	epd_spi_write (0x70);
	epd_spi_write (register_index);

	EPD_cs_high ();
	Wait_10us ();
	EPD_cs_low ();

	epd_spi_write (0x72);
	while(length--) {
		epd_spi_write (*register_data++);
	}
	EPD_cs_high ();
}


void epd_spi_send_byte (uint8_t register_index, uint8_t register_data) {
	EPD_cs_low ();
	epd_spi_write (0x70);
	epd_spi_write (register_index);

	EPD_cs_high ();
	Wait_10us ();
	EPD_cs_low ();
	epd_spi_write (0x72);
	epd_spi_write (register_data);
	EPD_cs_high ();
}



void EPD_display_hardware_init(void) {
	EPD_initialize_gpio();
	EPD_Vcc_turn_off();
	epd_spi_init();
	EPD_cs_low();
	EPD_pwm_low();
	EPD_rst_low();
	EPD_discharge_low();
	EPD_border_low();
}

