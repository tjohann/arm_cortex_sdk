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

#include "libavrhelper.h"


/*
 * -> convert usigned short data to data_string
 */
void
helper_convert_ushort_to_string(unsigned char data_string[], unsigned short data)
{
	data_string[4] = 0x30 + (data % 10);
	data_string[3] = 0x30 + ((data / 10) % 10);
	data_string[2] = 0x30 + ((data / 100) % 10);
	data_string[1] = 0x30 + ((data / 1000) % 10);
	data_string[0] = 0x30 + (data / 10000);
}


/*
 * -> convert usigned char data to data_string
 */
void
helper_convert_uchar_to_string(unsigned char data_string[], unsigned char data)
{
	data_string[2] = 0x30 + (data % 10);
	data_string[1] = 0x30 + ((data / 10) % 10); 
	data_string[0] = 0x30 + (data / 100);
}
