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
#include <libavrhelper.h>


#ifndef F_CPU
#  error "Freq of CPU not defined!"
#endif


/*
 * lcd specific error codes
 */
typedef enum lcd_errors {
	LCD_INIT_DEFAULT = 0x00, 
	LCD_UNKNOWN
} lcd_errors_t;



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
 */
void 
lcd_setup_display(void);



#endif
