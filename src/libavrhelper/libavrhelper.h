/*
  libavrhelper/libarmhelper - simple lib with common helper functions/macros for small
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

#ifndef _LIBAVRHELPER_H_
#define _LIBAVRHELPER_H_

/*
 * include some usefull header by default
 */
#include <avr/io.h>
#include <stdlib.h>

/*
 * common defines
 */
// define on and off 
#define MY_ON = 1;
#define MY_OFF = 0;

/*
 * my common errors
 */
#define MY_OK 0
#define MY_ERROR -1
// #define MY_... ?


/*
 * common macros
 */
#ifndef SET_BIT
#define SET_BIT(sfr, bit)			\
	(_SFR_BYTE(sfr) |= (1 << bit))		
#endif

#ifndef CLEAR_BIT	
#define CLEAR_BIT(sfr, bit)			\
	(_SFR_BYTE(sfr) &= ~(1 << bit))		
#endif

#ifndef TOGGLE_BIT
#define TOGGLE_BIT(sfr, bit)			\
	(_SFR_BYTE(sfr) ^= (1 << bit))		
#endif

/*
 * -> dummy function
 */
void 
helper_dummy(void);


#endif
