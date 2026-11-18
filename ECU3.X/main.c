/*
 * File:   main.c
 * Author: Purushothama k
 *
 */


#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"

#include "timer0.h"

static void init_leds() 
{
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();

    /* ECU1 main loop */
    const unsigned char name[] = "SP  GE  RPM  IND";
    clcd_print(name, LINE1(0));
    while (1) 
    {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }
}
