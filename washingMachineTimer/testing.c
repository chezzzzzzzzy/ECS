#include <xc.h>
#include"amt.h"
#include"stdio.h"
#include"rtc.h"

void interrupt HighISR(void){
    timer_callback();
}

void main(void) {
    LCD8init();
    timer_init();
    char buffer[20];
    TRISBbits.RB0 =1; 
    start_timer();
    while(1){
        LCD8send(0x80,0);
        LCD8send(0x01,0);

            sprintf(buffer, "%        ld", get_timeElapsed());
            for (int i = 0; buffer[i] != 0; i++) {
                LCD8send(buffer[i], 1);
        }
            if(PORTBbits.RB0 = 0){          // reset timer upon RBO pressed
                start_timer();
            }
        }
    }