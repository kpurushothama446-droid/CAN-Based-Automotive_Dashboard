#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;

int sec;
void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    
        clcd_print(data, LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
        clcd_print(data, LINE2(5));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
        clcd_print(data, LINE2(9));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    
            static unsigned char ind_state = 0;

    if (data[0] == 1 && data[1] == 0)
    {
        if (sec == 1)
        {
            sec = 0;
            ind_state ^= 1;          // ? TOGGLE
        }

        if (ind_state)
            LEFT_IND_ON();
        else
            LEFT_IND_OFF();

        RIGHT_IND_OFF();
        clcd_print("<-", LINE2(14));
    }
    else if (data[1] == 1 && data[0] == 0)
    {
        if (sec == 1)
        {
            sec = 0;
            ind_state ^= 1;          // ? TOGGLE
        }

        if (ind_state)
            RIGHT_IND_ON();
        else
            RIGHT_IND_OFF();

        LEFT_IND_OFF();
        clcd_print("->", LINE2(14));
    }
    else
    {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
        ind_state = 0;               // reset when no indicator
    }

}

void process_canbus_data() 
{   
    //process the CAN bus data
    uint16_t msg_id;
    uint8_t len;
    unsigned char data[7];
    
    can_receive(&msg_id, data, &len);
    
    if (msg_id == SPEED_MSG_ID)
    {
        data[len] = '\0';
        handle_speed_data(data, len);
    }
    else if(msg_id == GEAR_MSG_ID)
    {
        data[len] = '\0';
        handle_gear_data(data, len);
    }
    else if(msg_id == RPM_MSG_ID)
    {
        data[len] = '\0';
        handle_rpm_data(data, len);
    }
    else if(msg_id == INDICATOR_MSG_ID)
    {
        data[len] = '\0';
        handle_indicator_data(data, len);
    }
}
