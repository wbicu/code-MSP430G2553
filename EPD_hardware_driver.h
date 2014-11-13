#ifndef 	DISPLAY_HARDWARE_DRIVCE_H_INCLUDED_
#define 	DISPLAY_HARDWARE_DRIVCE_H_INCLUDED_

#include "Pervasive_Displays_small_EPD.h"

#define SMCLK_FREQ			(16000000)

/**SPI Defines ****************************************************************/
#define SPISEL              P1SEL
#define SPISEL2             P1SEL2
#define SPIIE			    IE2
#define SPICTL0				UCB0CTL0
#define SPICTL1				UCB0CTL1
#define SPIBR0				UCB0BR0
#define SPIBR1				UCB0BR1
#define SPIMCTL			    UCA0MCTL
#define SPIIFG				IFG2
#define SPIRXBUF			UCB0RXBUF
#define SPIRXIFG			UCB0RXIFG
#define SPITXBUF			UCB0TXBUF
#define SPITXIFG			UCB0TXIFG
#define SPISTAT				UCB0STAT
#define SPI_baudrate        (SMCLK_FREQ/COG_SPI_baudrate)           /**< the baud rate of SPI */

void epd_spi_init (void);
void epd_spi_attach (void);
void epd_spi_detach (void);
void epd_spi_send (unsigned char Register, unsigned char *Data, unsigned Length);
void epd_spi_send_byte (uint8_t Register, uint8_t Data);
void epd_spi_write (unsigned char Data);
void sys_delay_ms(unsigned int ms);
void start_EPD_timer(void);
void stop_EPD_timer(void);
uint32_t get_current_time_tick(void);
void set_current_time_tick(uint32_t count);
void PWM_start_toggle(void);
void PWM_stop_toggle(void);
void PWM_run(uint16_t time);
void EPD_display_hardware_init (void);

#endif 	//DISPLAY_HARDWARE_DRIVCE_H_INCLUDED_
