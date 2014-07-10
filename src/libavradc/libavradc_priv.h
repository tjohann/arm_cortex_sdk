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

#ifndef _LIBAVRADC_PRIV_H_
#define _LIBAVRADC_PRIV_H_

#include <libavrhelper.h>
#include "libavradc.h"
#include <avr/io.h>
#include <stdlib.h>


/*
 * serial errno stuff
 *
 * Note: of course not reentrant 
 *       ADC_ERROR is the general switch
 *       ADC_ERRNO for adc_errno which holds adc_error_t values 
 */
#ifdef ADC_ERROR 
#ifndef ADC_ERRNO
#define ADC_ERRNO
unsigned char adc_errno = MY_OK;
#endif
#else
# warning "No special serial error indication!"
#endif

/*
 * error string 
 */
unsigned char *adc_error_string = (unsigned char *) "ADC_ERROR";

/*
 * -> macros for setting ....
 */




#endif
