#include "LCD.h"
#include "lpc214x.h"

int main()
{
    PINSEL0  = 0x00000000;
    PINSEL1  = 0x00000000;
	PINSEL2  = 0x00000000;
	IODIR0 |= (1 << 10);
	IODIR0 |= (1 << 11);
	IODIR0 |= (1 << 20);
	IODIR1 |= (0xFF << 20);
//IODIR0 = 0x00100c00;
//	IODIR1= 0x00FF0000;
    lcd_init();

    while (1)
    {
        lcd_put_cur(0, 0);
        lcd_send_string("FERGUSSON");
        lcd_put_cur(1, 0);
        lcd_send_string("COLLEGE");
    }
}
