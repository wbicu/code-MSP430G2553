#ifndef EPAPER_H_INCLUDED
#define EPAPER_H_INCLUDED


#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <msp430g2553.h>

typedef void (*EPD_read_flash_handler)(long flash_address,uint8_t *target_buffer,
		uint8_t byte_length);

#if !defined(FALSE)
#define FALSE 0 /**< define FALSE=0 */
#endif

#if !defined(TRUE)
#define TRUE (1) /**< define TRUE=1 */
#endif

#if !defined(bool)
#define bool uint8_t
#endif

extern void delay_ms(unsigned int ms);

#define LINE_SIZE	64

enum EPD_SIZE {
	EPD_144,
	EPD_200,
	EPD_270
};
#include "conf_EPD.h"
#include "EPD_hardware_gpio.h"
#include "EPD_hardware_driver.h"
#include "EPD_COG_process.h"
#include "EPD_controller.h"

#endif	//EPAPER_H_INCLUDED



