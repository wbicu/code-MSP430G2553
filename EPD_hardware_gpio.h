

#include "Pervasive_Displays_small_EPD.h"

#ifndef DISPLAY_HARDWARE_GPIO_H_INCLUDED
#define DISPLAY_HARDWARE_GPIO_H_INCLUDED

#define	_BV(bit)   (1 << (bit)) /**< left shift 1 bit */
#define	_HIGH      1            /**< signal high */
#define	_LOW       !_HIGH       /**< signal low */

//FOR MSP430
#define DIR_(x) 			    x ## DIR
#define DIR(x)				    (DIR_(x))
#define OUT_(x) 			    x ## OUT
#define OUTPORT(x) 			    (OUT_(x))
#define SEL_(x)				    x ## SEL
#define SEL(x)				    (SEL_(x))
#define SEL2_(x)			    x ## SEL2
#define SEL2(x)				    (SEL2_(x))
#define IN_(x) 				    x ## IN
#define INPORT(x) 			    (IN_(x))
#define REN_(x) 			    x ## REN
#define REN(x) 				    (REN_(x))
#define BITSET(x,y) 		    ((x) |= (y))
#define BITCLR(x,y) 		    ((x) &= ~(y))
#define BITINV(x,y) 		    ((x) ^= (y))

#define	config_gpio_dir_o(Port,Pin)  BITSET(DIR (Port), Pin) /**< set output direction for an IOPORT pin */
#define	config_gpio_dir_i(Port,Pin)  BITCLR(DIR (Port), Pin)  /**< set input direction for an IOPORT pin */
#define	set_gpio_high(Port,Pin)      BITSET (OUTPORT (Port), Pin) /**< set HIGH for an IOPORT pin */
#define	set_gpio_low(Port,Pin)       BITCLR (OUTPORT (Port), Pin)  /**< set LOW for an IOPORT pin */
#define	set_gpio_invert(Port,Pin)    BITINV(OUTPORT (Port),Pin) /**< toggle the value of an IOPORT pin */
#define	input_get(Port,Pin)          (INPORT (Port)  & Pin )   /**< get current value of an IOPORT pin */

/******************************************************************************
* GPIO Defines
*****************************************************************************/
#define Temper_PIN              BIT4
#define Temper_PORT             P1       /**< LaunchPad P1.4 */
#define SPICLK_PIN              BIT5
#define SPICLK_PORT             P1       /**< LaunchPad P1.5 */
#define EPD_BUSY_PIN            BIT0
#define EPD_BUSY_PORT           P2       /**< LaunchPad P2.0  */
#define PWM_PIN                 BIT1
#define PWM_PORT                P2       /**< LaunchPad P2.1  */
#define EPD_RST_PIN             BIT2
#define EPD_RST_PORT            P2       /**< LaunchPad P2.2 */
#define EPD_PANELON_PIN         BIT3
#define EPD_PANELON_PORT        P2       /**< LaunchPad P2.3  */
#define EPD_DISCHARGE_PIN       BIT4
#define EPD_DISCHARGE_PORT      P2       /**< LaunchPad P2.4  */
#define EPD_BORDER_PIN          BIT5
#define EPD_BORDER_PORT         P2       /**< LaunchPad P2.5  */
#define SPIMISO_PIN             BIT6
#define SPIMISO_PORT            P1       /**< LaunchPad P1.6  */
#define SPIMOSI_PIN             BIT7
#define SPIMOSI_PORT            P1       /**< LaunchPad P1.7  */
#define Flash_CS_PIN            BIT7
#define Flash_CS_PORT           P2       /**< LaunchPad P2.7  */
#define	Flash_CS_PORT_SEL	    (SEL (Flash_CS_PORT))
#define	Flash_CS_PORT_SEL2		(SEL2(Flash_CS_PORT))
#define EPD_CS_PIN              BIT6
#define EPD_CS_PORT             P2       /**< LaunchPad P2.6  */
#define	CS_PORT_SEL		        (SEL (EPD_CS_PORT))
#define	CS_PORT_SEL2		    (SEL2(EPD_CS_PORT))

bool EPD_IsBusy(void);
void EPD_cs_high (void);
void EPD_cs_low (void);
void EPD_flash_cs_high(void);
void EPD_flash_cs_low (void);
void EPD_rst_high (void);
void EPD_rst_low (void);
void EPD_discharge_high (void);
void EPD_discharge_low (void);
void EPD_Vcc_turn_off (void);
void EPD_Vcc_turn_on (void);
void EPD_border_high(void);
void EPD_border_low (void);
void EPD_pwm_low (void);
void EPD_pwm_high(void);
void SPIMISO_low(void);
void SPIMOSI_low(void);
void SPICLK_low(void);
void EPD_initialize_gpio(void);

#endif	//DISPLAY_HARDWARE_GPIO_H_INCLUDED


