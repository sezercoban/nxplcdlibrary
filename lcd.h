

#include "board.h"

#ifndef lcd
#define lcd

// LCD rs ve enable pinleri
#define rspin 10U
#define enablepin 11U

//LCD data pinleri
#define d4 2U
#define d5 3U
#define d6 10U
#define d7 11U

//LCD data pinleri için gpio ve port
#define LCDGPIO GPIOB
#define LCDPORT PORTB

//LCD rs ve enable pinleri için gpio ve port
#define LCDRSENABLEGPIO GPIOC
#define LCDRSENPORT PORTC

#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00

void LCD_initialization(void);
void LCD_PinInit(void);
void LCD_komutgonder(char komut);
void LCD_init(void);
void LCD_delay(uint32_t delaytime);
void LCD_portWriter(char value);
void LCD_clear(void);
void LCD_setcursor(uint8_t satir, uint8_t sutun);
void LCD_write(char source[]);
void LCD_verigonder(unsigned char komut);


#endif 




