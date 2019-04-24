#include <windows.h>

#define LEDPort 0x332
#define TRUE

const unsigned char Bin2LED[] = 
{
    0x00, 0x11, 0x22
}


void main(void) {
    unsigned char i, LEDval;
    i = 0;
    printf("lab1");
    
    while(TRUE){
        Sleep(1000);  
        LEDval = Bin2LED[i];
        _outp (LEDPort, LEDval);
        i++;
        
        if (i == 10) {
            i = 0;
            
        }
    }
    
}




