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

#include "libavradc.h"
#include "libavradc_priv.h"


/*
 * -> setup adc 
 */
void 
adc_setup_adc(void) 
{

/*
 * ADC SETUP FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	
	// do something

#if ADC_ERROR == __ON__
	adc_errno = ADC_INIT_DEFAULT;
#endif
	
#endif  // AVR


/*
 * ADC SETUP FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}

