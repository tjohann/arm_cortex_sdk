/*
  libavradc/libarmadc - simple library as a handle of adc stuff for small
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

#ifndef _LIBAVRADC_H_
#define _LIBAVRADC_H_

#include <avr_compile_macros.h>
#include <libavrhelper.h>


#ifndef F_CPU
#  error "Freq of CPU not defined!"
#endif


/*
 * serial specific error codes
 */
typedef enum adc_errors {
	ADC_INIT_DEFAULT = 0x00, 
	ADC_UNKNOWN
} adc_errors_t;


/*
 * adc errno stuff
 *
 * HOTWO: use adc_errno
 * -> a global variable is defined and set to default by 
 *    this lib -> unsigned char adc_errno = MY_OK;
 * -> in YOUR header file add the folling declaration
 *    extern unsigned char serial_errno; 
 * -> if something goes wrong, then the functions set adc_errno to 
 *    an value of adc_errors_t 
 * -> if everthing works fine, then adc_errno is set to MY_OK (see libavrhelper.h)
 * -> for an example see template.* in src/template
 *
 * Note: of course not reentrant 
 *       ADC_ERROR is the general switch
 *       ADC_ERRNO for adc_errno which holds adc_error_t values 
 *       unsigned char * adc_error_string = "ADC_ERROR" for a common error string
 * 
 * Hint: its only tested in small range of possible clock and baud rates ... so
 *       i am not shure if everthing works fine! 
 *
 */

#ifndef ADC_ERROR  
#define ADC_ERROR OFF  
#  warning "ADC_ERROR not defined, use OFF"
#endif


/*
 * ----------- functions for init/setup of ADC -----------
 */

/*
 * -> setup adc 
 */
void 
adc_setup_adc(void);



#endif
