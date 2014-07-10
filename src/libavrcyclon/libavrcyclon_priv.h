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

#ifndef _LIBAVRCYCLON_PRIV_H_
#define _LIBAVRCYCLON_PRIV_H_

#include <libavrhelper.h>
#include "libavrcyclon.h"
#include <avr/io.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h> 


#ifndef CYCLON_PORT
#  error "CYCLON_PORT not defined!"
#endif


#if CYCLON_PORT == __PORT_A__
#define LEDS_PORT PORTA
#ifdef DDRA
#define LEDS_DDR DDRA
#else
# warning "DDRA not available"
#endif
#elif CYCLON_PORT == __PORT_B__
#define LEDS_PORT PORTB
#define LEDS_DDR DDRB
#elif CYCLON_PORT == __PORT_C__
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#elif CYCLON_PORT == __PORT_D__
#define LEDS_PORT PORTD
#define LEDS_DDR DDRD
#else
# error "CYCLON_PORT not valid"
#endif


#endif
