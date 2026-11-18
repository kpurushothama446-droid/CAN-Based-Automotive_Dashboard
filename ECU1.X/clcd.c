/*
 * File:   clcd.c
 * Author: Purushothama k
 *
 */

#include <xc.h>
#include "clcd.h"
#define _XTAL_FREQ 20000000
void clcd_write(unsigned char byte, unsigned char control_bit)
{
	CLCD_RS = control_bit;  // RS = 0 for command, 1 for data
    CLCD_RW = 0;            // Always write mode
    CLCD_PORT = byte;       // Put data on PORTD

    CLCD_EN = 1;
    __delay_us(1);
    CLCD_EN = 0;

    // Mandatory LCD processing delay
    __delay_ms(2);
}

void init_clcd()
{
	TRISD = 0x00;       // Data lines
    TRISC &= 0xF8;      // RC0, RC1, RC2 outputs

    CLCD_RW = 0;

    __delay_ms(20);
    clcd_write(0x38, 0);   // 8-bit, 2-line
    __delay_ms(5);
    clcd_write(0x0C, 0);   // Display ON, cursor OFF
    __delay_ms(5);
    clcd_write(0x01, 0);   // Clear display
    __delay_ms(5);
    clcd_write(0x02, 0);   // Return home
    __delay_ms(5);
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	clcd_write(data, DATA_COMMAND);
}

