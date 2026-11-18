/*
 * File:   ecu2_sensor.c
 * Author: Purushothama k
 *
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "digital_keypad.h"
#include "ssd_display.h"
uint16_t get_rpm()
{
    //Implement the rpm function
       return read_adc(RPM_ADC_CHANNEL) * 60 / 10.23;
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
}

IndicatorStatus process_indicator(void)
{
    static unsigned char prev_key = 0;
    unsigned char key;

    key = read_digital_keypad(STATE_CHANGE);   // ? IMPORTANT

    if (key == SW1 && prev_key != SW1)
    {
        return e_ind_left;
    }
    else if (key == SW2 && prev_key != SW2)
    {
        return e_ind_right;
    }
    else if(key == SW3 && prev_key != SW3)
    {
        return e_ind_off;
    }
    prev_key = key;
}
