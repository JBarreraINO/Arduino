#ifndef OLED_h
#define OLED_h
#include <avr/pgmspace.h>
#include <inttypes.h>
class OLED 
{
 public:
 void LEDPIN_Init(unsigned char SCL_PIN,unsigned char SDA_PIN,unsigned char RST_PIN,unsigned char DC_PIN);
 void LED_Init(void);
 void LED_CLS(void);
 void LED_Set_Pos(unsigned char x,unsigned char y);//Set the coordinate
 void LED_WrDat(unsigned char data);   //Write Data
 void LED_WrCmd(unsigned char cmd);
 void LED_P6x8Char(unsigned char x,unsigned char y,char ch);
 void LED_P6x8Str(unsigned char x,unsigned char y,char ch[]);
 void LED_P8x16Str(unsigned char x,unsigned char y,char ch[]);
 void LED_PrintBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char bmp[]); 
 void LED_Fill(unsigned char dat);
 void LED_PrintValueC(unsigned char x, unsigned char y,char data);
 void LED_PrintValueI(unsigned char x, unsigned char y, int data);
 void LED_PrintValueF(unsigned char x, unsigned char y, float data, unsigned char num);
 void LED_PrintValueFP(unsigned char x, unsigned char y, unsigned int data, unsigned char num);
 void LED_PrintEdge(void);
 void LED_Cursor(unsigned char cursor_column, unsigned char cursor_row);
 private:
 unsigned char _datascl;
 unsigned char _datasda;
 unsigned char _datarst;
 unsigned char _datadc;
 void LED_PrintLine(void);
 void SetStartColumn(unsigned char d);
 void SetAddressingMode(unsigned char d);
 void SetColumnAddress(unsigned char a, unsigned char b);
 void SetPageAddress(unsigned char a, unsigned char b);
 void SetStartLine(unsigned char d);
 void SetContrastControl(unsigned char d);
 void Set_Charge_Pump(unsigned char d);
 void Set_Segment_Remap(unsigned char d);
 void Set_Entire_Display(unsigned char d);
 void Set_Inverse_Display(unsigned char d);
 void Set_Multiplex_Ratio(unsigned char d);
 void Set_Display_On_Off(unsigned char d);
 void SetStartPage(unsigned char d);
 void Set_Common_Remap(unsigned char d);
 void Set_Display_Offset(unsigned char d);
 void Set_Display_Clock(unsigned char d);
 void Set_Precharge_Period(unsigned char d);
 void Set_Common_Config(unsigned char d);
 void Set_VCOMH(unsigned char d);
 void Set_NOP(void);
 /*static const unsigned char SCL_PIN = 10; 
 static const unsigned char SDA_PIN = 9;  
 static const unsigned char RST_PIN = 13;  
 static const unsigned char DC_PIN = 11;*/
};
extern const unsigned char logo[];
extern const unsigned char F6x8[][6];
extern const unsigned char F8X16[];


#endif
