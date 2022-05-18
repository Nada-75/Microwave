#define DataPins 'B'
#define CTRLPins 'A'
//macros of CTRLPins
#define E  2
#define RS 3
#define RW 4

//Macros of commands
#define CLR_display   0x01
#define RShiftCurs    0x06
#define Turn_On       0x0F
#define Curs_1stRow   0x80
#define Curs_2ndRow   0xc0
#define Set_4bit      0x28
#define Set_8bit      0x38
#define CursOff_DisON 0x0c
#define Return_Home   0x02

//Functions Prototype
//void genericDelay(unsigned long time);
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_WriteStr(char * str);
//void lcd_send_char(unsigned char chr);
//void lcd_send_string(char *str);
//void lcd_move_curs(unsigned char row,unsigned char col);
//void clear_display();
void LCD_write(unsigned char data);
