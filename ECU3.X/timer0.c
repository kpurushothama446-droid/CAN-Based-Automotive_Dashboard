/*
 * File:   timer0.c
 * Author: Purushothama k
 
 */


#include <xc.h>
#include "timer0.h"

void init_timer0(void) 
{
    TMR0ON = 1;
    T08BIT = 1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 0;
    TMR0IE = 1;
    TMR0IF = 0;
}