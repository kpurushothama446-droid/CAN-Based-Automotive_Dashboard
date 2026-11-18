#include <xc.h>
#include "adc.h"
#include "ecu2_sensor.h"
#include "ssd_display.h"
#include "digital_keypad.h"
#include "can.h"
#include "msg_id.h"

#define _XTAL_FREQ 20000000

void init_config(void)
{
    init_digital_keypad();
    init_adc();
    init_can();
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;

}
unsigned char digit[4];

static unsigned char seg[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
int main(void)
{
    init_config();

    IndicatorStatus ind;
    uint16_t adc;
    unsigned int delay = 0, count = 0;
    unsigned char flag[3];
    
    uint16_t msg_id;
    uint8_t len;
    unsigned char data[4];
    while (1)
    {
        adc = get_rpm();

        digit[3] = (adc % 10) + '0';
        digit[2] = ((adc / 10) % 10) + '0';
        digit[1] = ((adc / 100) % 10) + '0';
        digit[0] = (adc / 1000) + '0';

        
        //display(digit);
        can_transmit(RPM_MSG_ID, digit, 4);
        __delay_ms(80);
     
        /* Indicator scan MUST be frequent */
        ind = process_indicator();
        
            if (ind == e_ind_left)
            {
                flag[0] = 1;
                flag[1] = 0;
                flag[2] = '\0';
            }
            else if (ind == e_ind_right)
            {
                flag[0] = 0;
                flag[1] = 1;
                flag[2] = '\0';
            }
            else if(ind == e_ind_off)
            {
                flag[0] = 0;
                flag[1] = 0;
                flag[2] = '\0';
            }
            can_transmit(INDICATOR_MSG_ID, flag, 3);
            __delay_ms(80);
        /*
            if(flag1 == 1)
            {
                LEFT_IND_ON();
                RIGHT_IND_OFF();
            }
            else if(flag2 == 1)
            {
                    count = 1;
                    RIGHT_IND_ON();
                    LEFT_IND_OFF();
            }
            else if(flag3 == 1)
            {
                count = 0;
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
        */
    }
}