#ifndef CONF_EPD_H_INCLUDED
#define CONF_EPD_H_INCLUDED

#define EPD_KIT_TOOL_FUNCTIONS
#define COG_V110_G1
#define COG_SPI_baudrate 8000000
#define BUFFER_SIZE	1
#define PAYLOAD_SIZE 32

/** Firmware version to display on EPD Kit Tool  */
#define EPD_KIT_TOOL_VERSION	"1.11 "

/** \brief Kit ID for recognizing by EPD Kit Tool
 *
 * \note
 * - High byte is IC vendor, low byte is the name of supported development kit
 * - Texas Instruments=01, MSP430 LaunchPad=01 */
#define EPD_KIT_TOOL_ID			(uint16_t)0x0101

#endif /* CONF_EPD_H_INCLUDED */

