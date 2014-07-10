/*
  template - simple template for using my avr_sdk and libs for small 
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

#include "template.h"

/*
 * common defines
 * 
 * -> DELAYTIME ... the normal blink time
 * -> DELAYTIME_ON_ERROR ... the blinking time to indicate an error
 *
 * -> STATE_UNKNOWN ... state of template is unknown 
 * -> STATE_OK ... everthing is up and running
 * -> STATE_ERROR ... an error occured
 * -> STATE_INIT_DONE ... init finished
 * -> STATE_SERIAL_INIT_DONE ... init of serial finished -> used serial 
 *                               in error_indication 
 */
#define DELAYTIME 1000
#define DELAYTIME_ON_ERROR 100

// Note: incrising values ... do not change
#define STATE_UNKNOWN 0x00
#define STATE_OK 0x01
#define STATE_ERROR 0x02
#define STATE_SERIAL_INIT_DONE 0x03
#define STATE_INIT_DONE 0x04

// my common state info
unsigned char state_of_template = STATE_UNKNOWN;


/*
 * -> init hw
 */
void 
__attribute__((noinline)) init_template(void) 
{
	// set ddr for led pin
	SET_BIT(LED_DDR, LED_PIN);            
}


/*
 * -> let the led blink on errors or send error_string via serial
 */
void
error_indication(const unsigned char *error_string,
		 const unsigned char size) 
{
	if (state_of_template >= STATE_SERIAL_INIT_DONE) {
		serial_send_string(error_string, size); 
		
	} else {
		while (1) {
			SET_BIT(LED_PORT, LED_PIN);
			_delay_ms(DELAYTIME_ON_ERROR);
			
			CLEAR_BIT(LED_PORT, LED_PIN);
			_delay_ms(DELAYTIME_ON_ERROR);
		}
	}
}

/*
 * set LED on PB0 and clears it after DELAYTIME
 */
int 
__attribute__((OS_main)) main(void) 
{
	const unsigned char greeting_string[] = "hello ... i'm an atmega168(pa)\n\r";
	const unsigned char error_string[] = "an error occured ... pls check\n\r";

	unsigned char *string = NULL;
	unsigned char byte = 0x31;

	/*
	 * ---------- cyclon stuff ----------
	 */


	/*
	 * ---------- helper stuff ----------
	 */
	helper_dummy();

	/*
	 * ---------- serial stuff ----------
	 */
	// init serial and let the led blink with DELAYTIME_ON_ERROR ms
	serial_setup_async_normal_mode(DATA_8_STOP_1_NO_PARITY);
	if (serial_errno != MY_OK)
		error_indication(error_string, sizeof(error_string));
	
	// init serial done ... send greetings to peer
	state_of_template = STATE_SERIAL_INIT_DONE;
	serial_send_string(greeting_string, sizeof(greeting_string));

	// get an char from peer and send it as ascii 
	byte = serial_receive_byte();
	serial_send_byte(byte, SERIAL_SEND_ASCII);	

	/*
	 * Note: untested functions of libavrserial are below ...
	 *       tested are above this comment
	 * Date: 06.07.2014
	 */
	//string = serial_receive_string(4);
	//serial_send_string(string, 2);	
	// -->  END of untested serial stuff

	/*
	 * ---------- adc stuff ----------
	 */
	adc_setup_adc();

	/*
	 * ---------- init template stuff ----------
	 */
	// infrastructure is ready to use ... so my init is the next step 
	init_template();

        /*
	 * ---------- cyclon stuff ----------
	 */
	cyclon_setup_port();
	cyclon_run(5, 0, 200);
	_delay_ms(2 * DELAYTIME);
	cyclon_double_run(5, 200);
	_delay_ms(2 * DELAYTIME);
	cyclon_run(5, 7, 200);


        /*
	 * ---------- main stuff below ----------
	 */
	_delay_ms(5 * DELAYTIME);

	while (1) {
		
		// send string led on
		SET_BIT(LED_PORT, LED_PIN);
		_delay_ms(DELAYTIME);
		
		// send string led off
		CLEAR_BIT(LED_PORT, LED_PIN);
		_delay_ms(DELAYTIME);
		
	}
}
