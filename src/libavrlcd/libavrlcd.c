/*
  libavrlcd/libarmlcd - simple library as a handle of lcd stuff for small
                        microcontroller(avr) and cortex-m3(arm) devices
 
  Copyright (C) 2014 Thorsten Johannvorderbrueggen <thorsten.johannvorderbrueggen@t-online.de>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "libavrlcd.h"
#include "libavrlcd_priv.h"


/*
 * if you want to use LCD ... otherwise no code to to link
 */
#if USE_LCD == __YES__


/*
 * -> setup lcd (HD44780 or compatible)
 */
void 
lcd_setup_display(void) 
{

/*
 * LCD SETUP FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__

	/*
	 * usefull state after power on
	 *
	 * -> D0-D7 low
	 * -> EN high 
	 * -> RS low (commands)
	 * -> RW low (write)
	 */

	// setup db port
	LCD_DDR = 0xFF;	
	LCD_PORT &= ~0xFF;
	
	/*
	 * setup ctrl pins
	 *
	 * Notes: Pinning
	 *        - RS <-> register select <-> 0 command bytes, 1 character bytes
	 *        - EN <-> enable <-> transfer bytes on high to low transistion (write)
	 *                        <-> transfer bytes on a low to high transition (read)
	 *                            bytes are then available until a new low to high
	 *                            transistion
	 *        - RW <-> read/write <-> 0 write bytes to lcd, 1 read bytes from display
	 *        =====
	 *        Order/Timing
	 *        - EN should be 0 as default 
	 *        - EN periode > 1us (0-1-0-1) ... pulse width < 0,5us
	 *        - RS and RW could be set/clear together
	 *        1. set/clear RS
	 *        2. set/clear RW
	 *           - >140ns
	 *        3. EN 0->1
	 *        4. set DB
	 *        5. EN 1->0
	 *        6. clear/set RW
	 *        7. clear/set RS
	 */
	LCD_CTRL_DDR |= (1 << LCD_RS_PIN) | (1 << LCD_EN_PIN);
	LCD_CTRL_PORT &= ~( (1 << LCD_RS_PIN) | (1 << LCD_EN_PIN) );

	_delay_ms(LCD_BOOTUP_TIME);  // 100ms

	/*
	 * reset the lcd with special case ot the function set
	 *
	 * Note: - normally the hd44780 has a reset sequence which init the
	 *         controller after power on, but the power unit must 
	 *         behave in a special way 
	 *       - also the lcd must get an reset if the controller get an reset
	 *       =====
	 *       - the order of the function sets is a must
	 *       - the same for most the values (only change 0x38 if needed) 
	 */
	lcd_reset_lcd();
	
	/*
	 * - 8 bit mode
	 * - 2 logical lines 
	 * - 5x7 fonts
	 */
	LCD_PORT = 0x38;
	LCD_PUSH_EN_BUTTON();

	/*
	 * - display on/off control instruction 
	 */
	LCD_PORT = LCD_CMD_DISPLAY_OFF;
	LCD_PUSH_EN_BUTTON();
	
	/*
	 * - clear display
	 */
	LCD_PORT = LCD_CMD_CLEAR_LCD;
       	LCD_PUSH_EN_BUTTON();
	_delay_ms(LCD_INIT_LONG);

	/*
	 * - cursor auto increment
	 */
	LCD_PORT = 0x06;
	LCD_PUSH_EN_BUTTON();

	// ------ init done ------

	/*
	 * custom values:
	 *
	 * - display on
	 * - blinking cursor with
	 * - underline
	 */
	LCD_PORT = 0x0F;
	LCD_PUSH_EN_BUTTON();
	_delay_ms(LCD_INIT_LONG);

	// enable character mode -> default 
	LCD_CTRL_PORT |= (1 << LCD_RS_PIN);
	
#endif  // AVR


/*
 * ADC SETUP FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}


/*
 * ->  reset lcd  
 */
void 
lcd_reset_lcd() 
{

/*
 * RESET LCD FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__

	/*
	 * reset the lcd with special case ot the function set
	 */

	LCD_PORT = 0x30;
	LCD_PUSH_EN_BUTTON();
	_delay_ms(LCD_INIT_LONG);  // the first takes quite long -> around 4 ms

	LCD_PORT = 0x30;
	LCD_PUSH_EN_BUTTON();
	_delay_us(LCD_ENABLE_PAUSE_DOUBLE); // +200us

	LCD_PORT = 0x30;
	LCD_PUSH_EN_BUTTON();
	_delay_us(LCD_ENABLE_PAUSE_DOUBLE); // +200us

	// now the hd44780 is ready to receive the first normal function set

#endif
	

/*
 * RESET LCD FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}



/*
 * ----------- functions to send commands to the LCD ---------
 */

/*
 *  -> set cursor to position
 */
void lcd_set_cursor(unsigned char x, lcd_lines_t line)
{
    unsigned char command;
 
    switch(line) {
    case LCD_LINE_1:    
	    command = LCD_CMD_DDRAM_ADDR + LCD_ADDR_LINE1 + x;
	    break;
	    
    case LCD_LINE_2:    
	    command = LCD_CMD_DDRAM_ADDR + LCD_ADDR_LINE2 + x;
            break;
	    
    case LCD_LINE_3:    
            command = LCD_CMD_DDRAM_ADDR + LCD_ADDR_LINE3 + x;
            break;
	    
    case LCD_LINE_4:    
            command = LCD_CMD_DDRAM_ADDR + LCD_ADDR_LINE4 + x;
            break;
	    
    default:
	    command = LCD_CMD_DDRAM_ADDR + LCD_ADDR_LINE1 + x;                              
#if LCD_ERROR == __ON__
		lcd_errno = LCD_SET_CURSOR_DEFAULT;
#endif
    }
    
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = command;
    LCD_PUSH_EN_BUTTON();
}


/*
 *  -> clear display
 */
void lcd_clear_display()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_CLEAR_LCD;
    LCD_PUSH_EN_BUTTON();
    _delay_ms(LCD_INIT_LONG);
}


/*
 *  -> set cursor to home position
 */
void lcd_set_cursor_to_home_pos()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_CURSOR_HOME;
    LCD_PUSH_EN_BUTTON();
}


/*
 *  -> turn the display off
 */
void lcd_set_display_off()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_DISPLAY_OFF;
    LCD_PUSH_EN_BUTTON();
}


/*
 *  -> turn the display on
 */
void lcd_set_display_on()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_DISPLAY_ON;
    LCD_PUSH_EN_BUTTON();
}


/*
 *  -> set cursor off
 */
void lcd_set_cursor_off()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_CURSOR_OFF;
    LCD_PUSH_EN_BUTTON();
}


/*
 *  -> set cursor off
 */
void lcd_set_cursor_on()
{  
    LCD_SET_RS_TO_COMMAND();
    LCD_PORT = LCD_CMD_DISPLAY_ON;
    LCD_PUSH_EN_BUTTON();
}


/*
 * ----------- functions to send character to the LCD --------
 */

/*
 * -> send a character to the lcd
 */
void 
lcd_send_character(unsigned char data) 
{

/*
 * SEND CHARACTER FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	LCD_SET_RS_TO_CHARACTER();
	LCD_PORT = data;
	LCD_PUSH_EN_BUTTON();
#endif
	

/*
 * SEND CHARACTER FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}


/*
 * -> send a string to the lcd
 */
void 
lcd_send_string(const unsigned char *data) 
{
	unsigned char row_count = 0x00;
/*
 * SEND STRING FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	while((*data != '\0') && (row_count < LCD_NUMBER_OF_ROWS)) {
			lcd_send_character(*data++);
			row_count++;
	}
#if LCD_ERROR == __ON__
	if (*data != '\0') 
		lcd_errno = LCD_LINE_OVERFLOW;
#endif

#endif
	
/*
 * SEND STRING FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}


#else
# warning "USE_LCD == __NO__ -> dont try to use the functions "
#endif
