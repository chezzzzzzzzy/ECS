#include <xc.h>
#include "rtc.h"

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF 


volatile long time_in_millis;


void timer_init()
{
    PIR1bits.TMR2IF = 0; //Clear flag
    INTCONbits.GIEH = 0;
    RCONbits.IPEN = 1;   // Enable Priority Features \par
    IPR1bits.TMR2IP = 1; // Timer 2 is High Priority \par
    PIR1bits.TMR2IF = 0; // Clear Timer 2 Flag. \par
    PIE1bits.TMR2IE = 1; // Enable Timer 2 Interrupt. \par
    INTCONbits.GIEH = 1; // Enable Global Interrupt, High. \par
}

void start_timer()
{
    T2CONbits.TMR2ON = 0
    time_in_millis = 0; 
    T2CON = 0b01111111; //Prescaler = 16 Postscaler = 16 TMR2 on
    PR2 = 24;
    
}
void timer_callback() {    
    time_in_millis++; //increment loopCounter by 1 every 10ms
    PIR1bits.TMR2IF = 0;
}


long get_timeElapsed()
{   
    return time_in_millis;
}