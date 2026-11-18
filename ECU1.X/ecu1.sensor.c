/*
 * File:   ecu1.sensor.c
 * Author: Purushothama k
 *
 */


#include "ecu1_sensor.h"
#include "uart.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "msg_id.h"
#include "can.h"

#define _XTAL_FREQ 20000000
int flag = 0;
uint16_t get_speed(void)
{   
    uint16_t val;
    val = read_adc(CHANNEL4) / 10.33; 
    if(val > 99)
    {
        val = 99;
    }
    return val;
}
unsigned char get_gear_pos(void)
{
    return read_switches(STATE_CHANGE);
    
}


