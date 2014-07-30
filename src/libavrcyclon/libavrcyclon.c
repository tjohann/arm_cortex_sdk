/*
  libavrcyclon/libarmcyclon - simple knight rider lib for small microcontroller(avr) 
                              or cortex-m3(arm) devices 
 
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

#include "libavrcyclon.h"
#include "libavrcyclon_priv.h"


/*
 * if you want to use CYCLON ... otherwise no code to to link
 */
#if USE_CYCLON == __YES__

/*
 * -> do some init stuff 
 */
void
cyclon_setup_port(void)
{
	LEDS_DDR = 0xFF;
}

/*
 * -> cyclon eye function like knight rider
 */
void
cyclon_run(const unsigned short count, 
	   unsigned char starting_led,
	   double delay_time)
{
	uint8_t i = 0;
	uint16_t act_count = 0;

	if (starting_led < 8)
		i = starting_led;

	do {
		while (i < 7) {
			LEDS_PORT = (1 << i);
			_delay_ms(delay_time);
			i++;
		}
		
		while (i > 0) {
			LEDS_PORT = (1 << i);
			_delay_ms(delay_time);
			i--;
		}
		
		if (count != 0)
			act_count++;
		else
			act_count = 1;

		if (act_count == count) {
			LEDS_PORT = (1 << 0);
			_delay_ms(delay_time);
			LEDS_PORT = 0x00;
		}
		
	} while (act_count != count);
}


/*
 * -> cyclon double eye function like knight rider
 *
 * Note: led 0 + 7
 *       led 1 + 6
 *       ...
 */
void
cyclon_double_run(const unsigned short count, 
		  double delay_time)
{
	uint8_t i = 0;
	uint16_t act_count = 0;

	do {
		while (i < 3) {
			LEDS_PORT = (1 << i) | (1 << (7 - i));
			_delay_ms(delay_time);
			i++;
		}   

		while (i > 0) {
			LEDS_PORT = (1 << i) | (1 << (7 - i));
			_delay_ms(delay_time);
			i--;
		}   
		
		if (count != 0)
			act_count++;
		else
			act_count = 1;

		if (act_count == count) {
			LEDS_PORT = (1 << 0) | (1 << 7);
			_delay_ms(delay_time);
			LEDS_PORT = 0x00;
		}

	} while (act_count != count);
}

#else
# warning "USE_CYCLON == __NO__ -> dont try to use the functions "
#endif
