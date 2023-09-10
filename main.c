#include "LCD.h"
#include "lpc214x.h"

int main()
{
    PINSEL0  = 0x00000000;
    PINSEL1  = 0x00000000;
	PINSEL2  = 0x00000000;
	IODIR0 |= (1 << 10);  //EM
	IODIR0 |= (1 << 11);  //RS
	IODIR0 |= (1 << 20);  //RW
	IODIR1 |= (0xF << 20);
//IODIR0 = 0x00100c00;
//	IODIR1= 0x00FF0000;
    lcd_init();
	Delay(1000);
    while (1)
    {
        lcd_put_cur(0, 0);
        lcd_send_string("Embedded Systems");
		Delay(1000);
        lcd_put_cur(1, 0);
        lcd_send_string("Electronics");
		Delay(1000);
    }			  
}
