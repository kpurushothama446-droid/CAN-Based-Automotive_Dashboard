#include <xc.h>

extern int sec;
static int count;
void __interrupt() isr(void) 
{
    if(TMR0IF == 1)
    {
        count++;
        TMR0 = TMR0 + 8;
        TMR0IF = 0;
        if(count == 20000)
        {
            count = 0;
            sec++;
        }
    }
}
