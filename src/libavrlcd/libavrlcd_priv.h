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

#ifndef _LIBAVRLCD_PRIV_H_
#define _LIBAVRLCD_PRIV_H_

#include <libavrhelper.h>
#include "libavrlcd.h"
#include <avr/io.h>
#include <stdlib.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include <avr_defines_display.h>

/*
 * lcd errno stuff
 *
 * Note: of course not reentrant 
 *       LCD_ERROR is the general switch
 *       LCD_ERRNO for adc_errno which holds lcd_error_t values 
 */
#ifdef LCD_ERROR 
#ifndef LCD_ERRNO
#define LCD_ERRNO
unsigned char lcd_errno = MY_OK;
#endif
#else
# warning "No special lcd error indication!"
#endif

/*
 * error string 
 */
unsigned char *lcd_error_string = (unsigned char *) "LCD_ERROR";


/*
 * LCD timing 
 */
#define LCD_BOOTUP_TIME 100
#define LCD_ENABLE_PAUSE 100
#define LCD_ENABLE_PAUSE_DOUBLE 2*LCD_ENABLE_PAUSE
#define LCD_INIT_LONG 5


/*
 * LCD commands
 */
#define LCD_CMD_CLEAR_LCD 0x01
#define LCD_CMD_CURSOR_HOME 0x02
#define LCD_CMD_DISPLAY_OFF 0x08
#define LCD_CMD_DISPLAY_ON 0x0F
#define LCD_CMD_CURSOR_OFF 0x0C
#define LCD_CMD_DDRAM_ADDR 0x80


/*
 * -> macros for setting ....
 */
#define LCD_PUSH_EN_BUTTON() {				\
		LCD_CTRL_PORT |= (1 << LCD_EN_PIN);	\
		_delay_us(LCD_ENABLE_PAUSE);		\
		LCD_CTRL_PORT &= ~(1 << LCD_EN_PIN);	\
		_delay_us(LCD_ENABLE_PAUSE);		\
	}


#define LCD_SET_RS_TO_COMMAND() {			\
		LCD_CTRL_PORT &= ~(1 << LCD_RS_PIN);	\
	}

#define LCD_SET_RS_TO_CHARACTER() {	\
		LCD_CTRL_PORT |= (1 << LCD_RS_PIN);	\
	}


#define LCD_SET_EN_ZERO() {				\
		LCD_CTRL_PORT &= ~(1 << LCD_EN_PIN);	\
	}						


#define LCD_SET_EN_ONE() {				\
		LCD_CTRL_PORT |= (1 << LCD_EN_PIN);	\
	}						


/*
 * ----------- functions for init/setup of the LCD -----------
 */


/*
 * -> reset lcd  
 */
void
lcd_reset_lcd(void);



#endif
