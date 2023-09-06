#include <lpc214x.h>

#define bit(x) (1 << x)

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();

#define delay for(i = 0; i < 55000; i++)

unsigned int range = 0, i;

int main()
{
    VPBDIV = 0x01; // PCLK = 60MHz
    IO1DIR |= 0x00FF0000; // Set P1.16 to P1.23 as outputs for D0-D7
    IO0DIR |= bit(10) | bit(11); // P0.10 and P0.11 as outputs for EN and RS
    lcd_init();
    cmd(0x89);
    show("www.embetronicx.com");

    while (1)
    {
        cmd(0x18);
        delay;
    }
}

void lcd_init()
{
    cmd(0x02);
    cmd(0x28);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    IO1PIN &= 0xFFFF00FF; // Clear D4-D7 bits (P1.20 to P1.23)
    IO1PIN |= ((a & 0xF0) << 4); // Set D4-D7 bits with upper nibble of a
    IO0CLR |= bit(10); // EN = 0
    IO0CLR |= bit(11); // RS = 0
    IO0SET |= bit(10); // EN = 1
    lcd_delay();
    IO0CLR |= bit(10); // EN = 0

    IO1PIN &= 0xFFFF00FF; // Clear D4-D7 bits (P1.20 to P1.23)
    IO1PIN |= (((a << 4) & 0xF0) << 4); // Set D4-D7 bits with lower nibble of a
    IO0CLR |= bit(10); // EN = 0
    IO0CLR |= bit(11); // RS = 0
    IO0SET |= bit(10); // EN = 1
    lcd_delay();
    IO0CLR |= bit(10); // EN = 0
}

void dat(unsigned char b)
{
    IO1PIN &= 0xFFFF00FF; // Clear D4-D7 bits (P1.20 to P1.23)
    IO1PIN |= ((b & 0xF0) << 4); // Set D4-D7 bits with upper nibble of b
    IO0SET |= bit(10); // EN = 1
    IO0SET |= bit(11); // RS = 1 (Data mode)
    lcd_delay();
    IO0CLR |= bit(10); // EN = 0

    IO1PIN &= 0xFFFF00FF; // Clear D4-D7 bits (P1.20 to P1.23)
    IO1PIN |= (((b << 4) & 0xF0) << 4); // Set D4-D7 bits with lower nibble of b
    IO0SET |= bit(10); // EN = 1
    IO0SET |= bit(11); // RS = 1 (Data mode)
    lcd_delay();
    IO0CLR |= bit(10); // EN = 0
}

void show(unsigned char *s)
{
    while (*s)
    {
        dat(*s++);
    }
}

void lcd_delay()
{
    unsigned int i;
    for (i = 0; i <= 1000; i++)
        ;
}
