/*
 * lcd.h
 *
 *  Created on: 30.12.2018
 *      Author: rob
 */

#ifndef LCD_H_
#define LCD_H_

void lcd_init();
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_put_char(char c);
void lcd_write(const char *str);

#endif /* LCD_H_ */
