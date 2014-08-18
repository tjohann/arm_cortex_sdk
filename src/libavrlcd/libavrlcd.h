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

#ifndef _LIBAVRLCD_H_
#define _LIBAVRLCD_H_

#include <avr_compile_macros.h>


#ifndef F_CPU
#  error "Freq of CPU not defined!"
#endif


/*
 * LCD pinnig 
 *
 * Note: - only 8 bit mode 
 *       - RS <-> PC2
 *       - EN <-> PC3
 *       - RW <-> t.b.d.
 *
 *       see $(AVR_HOME)/include/avr_defines_display.h for more info
 */


/*
 * lcd specific error codes
 */
typedef enum lcd_errors {
	LCD_SET_CURSOR_DEFAULT = 0x00, 
	LCD_LINE_OVERFLOW,
	LCD_UNKNOWN
} lcd_errors_t;


/*
 * lcd lines
 */
typedef enum lcd_lines {
	LCD_LINE_1 = 0x00, 
	LCD_LINE_2,
	LCD_LINE_3,
	LCD_LINE_4
} lcd_lines_t;


/*
 * lcd errno stuff
 *
 * HOTWO: use lcd_errno
 * -> a global variable is defined and set to default by 
 *    this lib -> unsigned char lcd_errno = MY_OK;
 * -> in YOUR header file add the folling declaration
 *    extern unsigned char lcd_errno; 
 * -> if something goes wrong, then the functions set lcd_errno to 
 *    an value of lcd_errors_t 
 * -> if everthing works fine, then lcd_errno is set to MY_OK (see libavrhelper.h)
 * -> for an example see template.* in src/template
 *
 * Note: of course not reentrant 
 *       LCD_ERROR is the general switch
 *       LCD_ERRNO for lcd_errno which holds lcd_error_t values 
 *       unsigned char * lcd_error_string = "LCD_ERROR" for a common error string
 * 
 */

#ifndef LCD_ERROR  
#define LCD_ERROR OFF  
#  warning "LCD_ERROR not defined, use OFF"
#endif


/*
 * ----------- functions for init/setup of the LCD -----------
 */

/*
 * -> setup lcd 
 *
 * Note: includes call lcd_reset_lcd()
 *       =====
 *       Config: - 8 bit mode
 *               - 2 logical lines 
 *               - 5x7 fonts
 *               - blinking cursor with
 *               - underline
 *               - cursor auto increment
 */
void 
lcd_setup_display(void);


/*
 * -> reset lcd  
 *
 * Note: see lcd_setup_display for init values
 */
void
lcd_reset_lcd(void);

/*
 * ----------- functions to send commands to the LCD ---------
 */

/*
 *  -> clear display
 */
void lcd_clear_display();


/*
 *  -> set cursor to home position
 */
void lcd_set_cursor_to_home_pos();


/*
 *  -> set cursor to position
 */
void lcd_set_cursor(unsigned char x, lcd_lines_t line);


/*
 *  -> turn the display off
 */
void lcd_set_display_off();


/*
 *  -> turn the display on
 */
void lcd_set_display_on();


/*
 *  -> set cursor off
 */
void lcd_set_cursor_off();


/*
 *  -> set cursor off
 */
void lcd_set_cursor_on();


/*
 * ----------- functions to send character to the LCD --------
 */

/*
 * -> send a character to the lcd
 */
void 
lcd_send_character(unsigned char data);


/*
 * -> send a string to the lcd
 *
 * Note: if a line is longer than LCD_NUMBER_OF_ROWS, then
 *       lcd_errno is set to LCD_LINE_OVERFLOW
 */
void 
lcd_send_string(const unsigned char *data);

#endif
