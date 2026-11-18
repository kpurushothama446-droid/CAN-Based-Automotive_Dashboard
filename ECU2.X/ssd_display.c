#include <xc.h>
#include "ssd_display.h"

void init_ssd_control(void)
{
    TRISD = 0x00;   // SSD segments

    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;

    // RA5 untouched (ADC)
}

/* Better if implemented in timer handler */
extern unsigned char digit[];
void display(unsigned char data[])
{
	unsigned int wait;
	unsigned char i;

	for (i = 0; i < 4; i++)
	{
        SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
		SSD_DATA_PORT = data[i];
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (1 << i);

		for (wait = 1000; wait--; );
	}
}