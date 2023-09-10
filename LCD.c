#include "lpc214x.h"
#include "LCD.h"

void Delay(unsigned int time)
{
unsigned int i, j;
for(i=0; i<time; i++)
	for(j-=0; j<10000; j++);
}

void lcd_init (void)
{

	Delay(1000);
	lcd_send_cmd(0x02);
	Delay(1000);
	lcd_send_cmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	Delay(1000);
	lcd_send_cmd(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	Delay(1000);
	lcd_send_cmd(0x01);  // clear display
	Delay(1000);
	lcd_send_cmd(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	Delay(1000);
	lcd_send_cmd(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	Delay(1000);
}


void send_to_lcd(char data, int rs)
{
    // Set or clear RS pin (P0.11) based on the 'rs' parameter
    if (rs == 1)
    {
        IOSET0 |= (1 << 11);  // Set RS (Register Select) pin
		//IOCLR0 |= (	1<<	20);
		Delay(1000);
    }
    else
    {
        IOCLR0 |= (1 << 11);  // Clear RS (Register Select) pin
	//	IOCLR0 |= (	1<<	20);
		Delay(1000);
    }

    // Set data pins (P1.20 to P1.23) with the lower 4 bits of 'data'
    IOCLR1 |= 0xF << 20;    // Clear data pins (P1.20 to P1.23)
	Delay(1000);
    IOSET1 |= ((data) << 20);  // Set data pins with the lower 4 bits of 'data'
	Delay(1000);

    // Toggle EN (Enable) pin (P0.20) to send the data
    IOSET0 |= (1 << 10);  // Set EN (Enable) pin
    Delay(1000);            // Delay for a short duration
    IOCLR0 |= (1 << 10);  // Clear EN (Enable) pin to finish sending
    Delay(1000);            // Delay for a short duration
}



void lcd_send_cmd(unsigned char cmd)
{
  	
	char datatosend;
	//Send Upper nibble firsr
	datatosend = ((cmd>>4) & 0x0F);
	send_to_lcd(datatosend,0);
	 Delay(100);


	// Send lower nibble
	datatosend = ((cmd) & 0x0F);
	send_to_lcd(datatosend,0);
	Delay(1000); 
}


void lcd_send_data(unsigned char data)
{
	char datatosend;
	
	//Send the higher nibble first
	datatosend = ((data >>4) & 0x0F);
	send_to_lcd(datatosend,1);
    Delay(1000);
	//send lower nibble
	datatosend = data & (0x0F);
	send_to_lcd(datatosend,1);
	Delay(1000);

}


void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}



void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
