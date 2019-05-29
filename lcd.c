
#include "lcd.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

//bekleme komutu
void LCD_delay(uint32_t delaytime)
{
	uint32_t i;
	delaytime = delaytime * 10; // 10 kat olmalı
		for(i=0; i<delaytime; i++)
		{
			__asm("nop");
		}
}
// lcd giriş fonksiyonu
void LCD_initialization() {
	LCD_PinInit();
	LCD_init();
}

//lcd ekran temizleme
void LCD_clear()
{
	LCD_komutgonder(0x01);
}

//lcd ekran imleç tanımlama
void LCD_setcursor(uint8_t satir, uint8_t sutun)
{
	if(satir == 1)
		LCD_komutgonder(0x80|(sutun-1));

	if(satir==2)
		LCD_komutgonder(0x80|(0x40+(sutun-1)));
}


//lcd ekranına yazma fonksiyonu
void LCD_write(char source[])
{
	int i;
	for (i = 0; i < strlen(source); i++)
	{
		LCD_verigonder(source[i]);
	}
}

// core fonksiyonları 

void LCD_PinInit(void)
{
	gpio_pin_config_t outputConfig = {kGPIO_DigitalOutput, 0,};

	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortB);



    PORT_SetPinMux(LCDRSENPORT, rspin, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCDRSENPORT, enablepin, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCDPORT, d4, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCDPORT, d5, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCDPORT, d6, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCDPORT, d7, kPORT_MuxAsGpio);

	GPIO_PinInit(LCDRSENABLEGPIO, rspin, &outputConfig);
	GPIO_PinInit(LCDRSENABLEGPIO, enablepin, &outputConfig);
	GPIO_PinInit(LCDGPIO, d4, &outputConfig);
	GPIO_PinInit(LCDGPIO, d5, &outputConfig);
	GPIO_PinInit(LCDGPIO, d6, &outputConfig);
	GPIO_PinInit(LCDGPIO, d7, &outputConfig);
}

void LCD_init(void)
{
	int i = 0;


	GPIO_WritePinOutput(LCDRSENABLEGPIO, rspin, 0);

	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 0);
	LCD_delay(3000);

	for(i=0;i<=3;i++)
	{
	   LCD_komutgonder(0x03);
	   LCD_delay(5000);
	}

	LCD_komutgonder(0x02);
	LCD_komutgonder(0x28);
	LCD_komutgonder(0x08);
	LCD_komutgonder(0x0C);
	LCD_komutgonder(0x06);
	LCD_komutgonder(0x01);
}

void  LCD_komutgonder(char komut)
{


	LCD_portWriter(komut>>4);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, rspin, 0);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 0);
	LCD_delay(2000);

	LCD_portWriter(komut&0x0F);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, rspin, 0);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 0);
	LCD_delay(2000);
}

void LCD_portWriter(char value)
{

		GPIO_WritePinOutput(LCDGPIO, d4,  (value >>0) & 0x01);
		LCD_delay(50);
		GPIO_WritePinOutput(LCDGPIO, d5,  (value >> 1) & 0x01);
		LCD_delay(50);
		GPIO_WritePinOutput(LCDGPIO, d6,  (value >> 2) & 0x01);
		LCD_delay(50);
		GPIO_WritePinOutput(LCDGPIO, d7,  (value >> 3) & 0x01);
		LCD_delay(50);

}





void LCD_verigonder(unsigned char komut)
{
	LCD_portWriter(komut>>4);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, rspin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 0);
	LCD_delay(2000);

	LCD_portWriter(komut&0x0F);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, rspin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 1);
	LCD_delay(50);
	GPIO_WritePinOutput(LCDRSENABLEGPIO, enablepin, 0);
	LCD_delay(2000);
}
