#ifndef DISPLAY_COG_PROCESS__H_INCLUDED
#define DISPLAY_COG_PROCESS__H_INCLUDED

#include "Pervasive_Displays_small_EPD.h"
/**
 * \brief The definition for driving stage to compare with for getting Odd and Even data  */
#define BLACK0   (uint8_t)(0x03) /**< getting bit1 or bit0 as black color(11) */
#define BLACK1   (uint8_t)(0x0C) /**< getting bit3 or bit2 as black color(11) */
#define BLACK2   (uint8_t)(0x30) /**< getting bit5 or bit4 as black color(11) */
#define BLACK3   (uint8_t)(0xC0) /**< getting bit7 or bit6 as black color(11) */
#define WHITE0   (uint8_t)(0x02) /**< getting bit1 or bit0 as white color(10) */
#define WHITE1   (uint8_t)(0x08) /**< getting bit3 or bit2 as white color(10) */
#define WHITE2   (uint8_t)(0x20) /**< getting bit5 or bit4 as white color(10) */
#define WHITE3   (uint8_t)(0x80) /**< getting bit7 or bit6 as white color(10) */
#define NOTHING0 (uint8_t)(0x01) /**< getting bit1 or bit0 as nothing input(01) */
#define NOTHING1 (uint8_t)(0x04) /**< getting bit3 or bit2 as nothing input(01) */
#define NOTHING2 (uint8_t)(0x10) /**< getting bit5 or bit4 as nothing input(01) */
#define NOTHING3 (uint8_t)(0x40) /**< getting bit7 or bit6 as nothing input(01) */
#define NOTHING  (uint8_t)(0x55) /**< sending Nothing frame, 01=Nothing, 0101=0x5 */


#define ALL_BLACK	 	 (uint8_t)(0xFF)
#define ALL_WHITE		 (uint8_t)(0xAA)
#define BORDER_BYTE_B    (uint8_t)(0xFF)
#define BORDER_BYTE_W    (uint8_t)(0xAA)
#define ERROR_BUSY       (uint8_t)(0xF0)
#define ERROR_COG_ID     (uint8_t)(0xF1)
#define ERROR_BREAKAGE   (uint8_t)(0xF2)
#define ERROR_DC         (uint8_t)(0xF3)
#define ERROR_CHARGEPUMP (uint8_t)(0xF4)
#define RES_OK           (uint8_t)(0x00)


#define LINE_BUFFER_DATA_SIZE 33
#define COG_line_Max_Size     33
/**
 * \brief Support 1.44", 2" and 2.7" three type EPD currently */
#define COUNT_OF_EPD_TYPE 3

/**
 * \brief Four driving stages */
enum Stage {
	Stage1, /**< Inverse previous image */
	Stage2, /**< White */
	Stage3, /**< Inverse new image */
	Stage4  /**< New image */
};

#if (defined COG_V110_G1)

struct COG_144_line_data_t {
	uint8_t border_byte;  /**< Internal border_control, for 1.44" EPD only */
	uint8_t even[16]; /**< 1.44" even byte array */
	uint8_t scan[24]; /**< 1.44" scan byte array */
	uint8_t odd [16]; /**< 1.44" odd byte array */
} ;


struct COG_200_line_data_t {
	uint8_t even[25]; /**< 2" even byte array */
	uint8_t scan[24]; /**< 2" scan byte array */
	uint8_t odd [25]; /**< 2" odd byte array */
	uint8_t dummy_data;	/**< dummy byte 0x00 */
} ;

struct COG_270_line_data_t {
	uint8_t even[33]; /**< 2.7" even byte array */
	uint8_t scan[44]; /**< 2.7" scan byte array */
	uint8_t odd [33]; /**< 2.7" odd byte array */
	uint8_t dummy_data;	/**< dummy byte 0x00 */
} ;


typedef union {
	union {
		struct COG_144_line_data_t line_data_for_144; /**< line data structure of 1.44" EPD */
		struct COG_200_line_data_t line_data_for_200; /**< line data structure of 2" EPD */
		struct COG_270_line_data_t line_data_for_270; /**< line data structure of 2.7" EPD */
	} line_data_by_size; /**< the line data of specific EPD size */
	uint8_t uint8[LINE_BUFFER_DATA_SIZE]; /**< the maximum line buffer data size as length */
} COG_line_data_packet_type;

/** 
 * \brief Define the COG driver's parameters */
struct COG_parameters_t {
	uint8_t   channel_select[8]; /**< the SPI register data of Channel Select */
	uint8_t   voltage_level;     /**< the SPI register data of Voltage Level */
	uint16_t  horizontal_size;   /**< the bytes of width of EPD */
	uint16_t  vertical_size;     /**< the bytes of height of EPD */
	uint8_t   data_line_size;    /**< Data + Scan + Dummy bytes */
	uint16_t  frame_time_offset; /**< the rest of frame time in a stage */
	uint16_t  stage_time;        /**< defined stage time */
} ;

extern const struct COG_parameters_t  COG_parameters[COUNT_OF_EPD_TYPE];
extern const uint8_t   SCAN_TABLE[4];
void EPD_init(void);
void EPD_power_on (void);
uint8_t EPD_initialize_driver (uint8_t EPD_type_index);
void EPD_display_from_array_prt (uint8_t EPD_type_index, unsigned char table[]);
void EPD_display_from_flash_prt (uint8_t EPD_type_index, long previous_image_flash_address,
	long new_image_flash_address,EPD_read_flash_handler On_EPD_read_flash);
uint8_t EPD_power_off (uint8_t EPD_type_index);
void COG_driver_EPDtype_select(uint8_t EPD_type_index);

#endif 	//DISPLAY_COG_PROCESS__H_INCLUDED
#endif
