#include "stdint.h"

void UART0Init();
uint8_t UART0_READAvailable();
char UART0_READ();
void UART0_WRITE(char c);
void getCommand(char *str, uint8_t maxlen);
void UART_printStr(char *str);
