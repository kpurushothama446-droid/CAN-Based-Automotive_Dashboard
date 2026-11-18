#include "ecu1_sensor.h"
#include "adc.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "uart.h"
#include "can.h"
#include "msg_id.h"
void init_config(void)
{ 
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_can();
}
#define _XTAL_FREQ 20000000  
int flag = 0;
char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};
int main(void)
{
    
   
    init_config();
    
    unsigned char name[16] = "Speed     Gear";
    unsigned char key;
    unsigned char speed[3];
    unsigned int index = 0;
    
    uint16_t msg_id;
    uint8_t len;
    uint8_t data[8];
    while(1)
    {
        clcd_print(name, LINE1(0));

        uint16_t adc = get_speed();

        speed[0] = (adc / 10) + '0';
        speed[1] = (adc % 10) + '0';
        speed[2] = '\0';

        key = get_gear_pos();

        if(key == MK_SW1)
        {
            if(flag == 1)
            {
                flag = 0;
                index = 0;
            }
            
            if(index < 7 &&  flag != 1)
            {
                index++;
            }
        }
        else if(key == MK_SW4)
        {
            if(flag == 1)
            {
                flag = 0;
                index = 0;
            }
            
            if(index > 0 && flag != 1)
            {
                index--;
            }
        }
        else if(key == MK_SW2)
        {
            index = 8;
            flag = 1;
        }
        can_transmit(SPEED_MSG_ID, speed, 2);
        __delay_ms(80);
       /*
        can_receive(&msg_id, data, &len);

        if (len && msg_id == SPEED_MSG_ID)
        {
            data[len] = '\0';
            clcd_print(data, LINE2(0));
        }
        * */

        can_transmit(GEAR_MSG_ID, event[index], 2);
        __delay_ms(80);
        
        /*
        can_receive(&msg_id, data, &len);

        if (len && msg_id == GEAR_MSG_ID)
        {
            data[len] = '\0';
            clcd_print(data, LINE2(12));
        }
*/
    }
}