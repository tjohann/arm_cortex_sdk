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
 * -> macros for setting ....
 */




#endif
