/*
  libavrserial/libarmserial - simple library as a handle for serial communication for 
                              small microcontroller(avr) and cortex-m3(arm) devices
 
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

#include "libavrserial.h"
#include "libavrserial_priv.h"


/*
 * -> setup USART0 for async mode at normal speed ... U2Xn=0
 */
void 
serial_setup_async_normal_mode(serial_frame_type_t frame_type)
{
	serial_setup_usart(ASYNC_NORMAL,
			   frame_type,
			   ENA_ALL);
}

/*
 * -> setup USART0 for async mode at double speed ... U2Xn=1
 */
void 
serial_setup_async_double_speed(serial_frame_type_t frame_type)
{
	serial_setup_usart(ASYNC_DOUBLE,
			   frame_type,
			   ENA_ALL);
}

/*
 * -> setup USART0 for sync master mode
 */
void 
serial_setup_sync_master(serial_frame_type_t frame_type)
{
       	serial_setup_usart(SYNC_MASTER,
			   frame_type,
			   ENA_ALL);
}


/*
 * -> setup USART0 for sync slave mode
 */
void 
serial_setup_sync_slave(serial_frame_type_t frame_type)
{
       	serial_setup_usart(SYNC_SLAVE,
			   frame_type,
			   ENA_ALL);
}



/*
 * ************** private functions **************
 */

/*
 * -> init USART
 */
void 
serial_setup_usart(serial_op_mode_t op_mode,
		   serial_frame_type_t frame_type,
		   serial_enable_rxtx_t ena_rxtx) 
{

/*
 * SERIAL SETUP FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__

        /*
	 * For baudmode see:
	 *
	 * util_setbaud <util/setbaud.h>: Helper macros for baud rate calculations
	 * #define F_CPU=1000000
	 * #define BAUD 9600
	 * -> include <util/setbaud.h>
	 * UBRR0H = UBRRH_VALUE;                      
	 * UBRR0L = UBRRL_VALUE; 
	 */
	UBRR0H = UBRRH_VALUE;                       
	UBRR0L = UBRRL_VALUE;	

	switch (op_mode) {
	case ASYNC_NORMAL:
		SERIAL_SET_ASYNC_MODE();
/*
 * Note: USE_2X handles the need of double speed or not (util_setbaud helper)
 *       see http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Der_UART for
 *       more informations (sry only in german)
 */
 
#if USE_2X
		SERIAL_ENA_DOUBLE_SPEED();
#else
		SERIAL_DIS_DOUBLE_SPEED()
#endif
		break;
	case ASYNC_DOUBLE:
		SERIAL_SET_ASYNC_MODE();	
#if USE_2X
		SERIAL_ENA_DOUBLE_SPEED();
#else
		SERIAL_DIS_DOUBLE_SPEED()
#endif
		break;
	case SYNC_MASTER:
		SERIAL_SET_SYNC_MODE();	
		/*
		 * -> TODO: fill me ...
		 */
		break;
	case SYNC_SLAVE:
		SERIAL_SET_SYNC_MODE();	
		/*
		 * -> TODO: fill me ...
		 */
		break;
	case MASTER_SPI:
		/*
		 * -> TODO: fill me ...
		 */
		break;
	default:
		// ASYNC_NORMAL
		SERIAL_DIS_DOUBLE_SPEED();
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_INIT_DEFAULT;
#endif
	}

	switch (ena_rxtx) {
	case ENA_ALL:
		SERIAL_ENA_ALL();
	       	break;
	case ENA_RX:
		SERIAL_DIS_TX();
		SERIAL_ENA_RX();
		break;
	case ENA_TX:
		SERIAL_DIS_RX();
		SERIAL_ENA_TX();	
		break;
	default:
		// enable TX and RX
		SERIAL_ENA_ALL();
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_INIT_DEFAULT;
#endif
	}

	switch (frame_type) {
	case DATA_8_STOP_1_NO_PARITY:
		SERIAL_SET_8_DATA_BITS();
		SERIAL_SET_1_STOP_BIT();
		SERIAL_SET_NO_PARITY();
		break;
	default:
		// DATA_8_STOP_1_NO_PARITY
		SERIAL_SET_8_DATA_BITS();
		SERIAL_SET_1_STOP_BIT();
		SERIAL_SET_NO_PARITY();
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_INIT_DEFAULT;
#endif
	}

	
#endif  // AVR

/*
 * SERIAL SETUP FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}


/*
 * -> send data (polling)
 */
void 
serial_send_data(const unsigned short data) 
{
	unsigned char send_data = 0x00;

/*
 * SEND_DATA FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	/*
	 * Check if UDRE0 (Data Register Empty) is set, 
	 * otherwise wait ... and wait ... 
	 *
	 * Note: 9 bit mode uses TXB8n for the 9. bit
	 */
	while (!(UCSR0A & (1 << UDRE0)))
		;

	if ((UCSR0B >> UCSZ02) & 1) { // 9 bit mode
		if (data & 0x0100)
			UCSR0B |= (1 << TXB80);
		else 
			UCSR0B &= ~(1 << TXB80);
        } 
		
	send_data = (0xFF) & data;
	UDR0 = send_data;   // will change state of send fifo       
	
#endif  // AVR

/*
 * SEND_DATA FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}

/*
 * -> send byte (polling)
 */
void 
serial_send_byte(const unsigned char byte,
		 serial_send_mode_t mode)
{
/*
 * SEND_DATA FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	/*
	 * Check if UDRE0 (Data Register Empty) is set, 
	 * otherwise wait ... and wait ... 
	 */
	while (!(UCSR0A & (1 << UDRE0)))
		;

	switch (mode)
	{
	case SERIAL_SEND_NORMAL:
		UDR0 = byte;   // will change state of send fifo       
		break;
	case SERIAL_SEND_ASCII:
		// first char
		UDR0 = 0x30 + (byte / 100);
		while (!(UCSR0A & (1 << UDRE0)))
			;
		// second char
		UDR0 = 0x30 + ((byte / 10) % 10);
		while (!(UCSR0A & (1 << UDRE0)))
			;
		// third char
		UDR0 = 0x30 + (byte % 10);
		break;
	default:
		// SERIAL_SEND_ASCII
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_RCV_DEFAULT;
#endif
		UDR0 = byte;        
	}

#endif  // AVR

/*
 * SEND_DATA FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

}


/*
 * -> send string (polling)
 */
void 
serial_send_string(const unsigned char *data_string, 
		   const unsigned char size) 
{
	unsigned char i = 0;

	// dont send nil 
	for(i = 0; i < (size - 1); i++)
		serial_send_byte(data_string[i], SERIAL_SEND_NORMAL);
}


/*
 * -> receive data (polling)
 */
unsigned short 
serial_receive_data(void) 
{
	unsigned short received_data = 0x0000;
	unsigned char data = 0x00, ninth_bit = 0x00; 
	unsigned char state_bits = 0x00, state = 0x00;

/*
 * RECEIVE_DATA FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	/*
	 * Check if RXC0 (Receive Complete Flag) is set, 
	 * otherwise wait ... and wait ... 
	 *
	 * Note: 9 bit mode uses RXB8n for the 9. bit
	 */
	while (!(UCSR0A & (1 << RXC0)))
		;

	/*
	 * addtional state bits 
	 *
	 * -> FEn Frame Error
	 * -> DORn Data OverRun
	 * -> UPEn USART Paraty Error
	 */
	state_bits = (1 << FE0) | (1 << DOR0) | (1 << UPE0);

	/*
	 * Note: the order is important 
	 */
	state = UCSR0A;
	ninth_bit = (UCSR0B >> RXB80) & 1;
	data = UDR0; // will change state of receive fifo

	if (state & state_bits) {
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_RCV_ERROR;
#endif		
		received_data = 0x00;
	} else {		
#if SERIAL_ERROR == __ON__
		serial_errno = MY_OK;
#endif
		received_data = (ninth_bit << 8) | data;
	}
#endif  // AVR


/*
 * RECEIVE_DATA FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

	return received_data;
}


/*
 * -> receive byte (polling)
 */
unsigned char 
serial_receive_byte(void) 
{
	unsigned char data = 0x00;
	unsigned char state_bits = 0x00, state = 0x00;

/*
 * RECEIVE_DATA FOR AVR
 */
#if CONTROLLER_FAMILY == __AVR__
	/*
	 * Check if RXC0 (Receive Complete Flag) is set, 
	 * otherwise wait ... and wait ... 
	 */
	while (!(UCSR0A & (1 << RXC0)))
		;

	/*
	 * check addtional state bits -> see serial_receive_data for more info
	 */
	state_bits = (1 << FE0) | (1 << DOR0) | (1 << UPE0);
	state = UCSR0A;
	if (state & state_bits) {
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_RCV_ERROR;
#endif		
		data = 0x00;
	} else {		
#if SERIAL_ERROR == __ON__
		serial_errno = MY_OK;
#endif
		data = UDR0; // will change state of receive fifo
	}
#endif  // AVR


/*
 * RECEIVE_DATA FOR ARM-CORTEX-M3
 */
#if CONTROLLER_FAMILY == __ARM__
	// fill me
#endif  // ARM

	return data;
}



/*
 * -> receive string (polling)
 *
 *  serial_errno: SERIAL_RCV_ERROR
 */
unsigned char *
serial_receive_string(unsigned char size)
{
	unsigned char *data = NULL;

	data = malloc(size);
	if (data == NULL) {
#if SERIAL_ERROR == __ON__
		serial_errno = SERIAL_RCV_ERROR;
#endif
		data = serial_error_string;
	}

	return data;
}

