#ifndef LCD_H
#define LCD_H

#include "lpc214x.h"  // Include the appropriate header for your microcontroller

// Function prototypes
void lcd_send_cmd(char cmd);
void lcd_init(void);
void send_to_lcd(char data, int rs);
void lcd_send_data(unsigned char data);
void lcd_put_cur(int row, int col);
void lcd_send_string(char *str);

#endif // LCD_H
