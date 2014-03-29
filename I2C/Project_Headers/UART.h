//LCD.h

#ifndef UART_H_
#define GPIO_PIN_MASK 0x1Fu 
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))

void UARTinit(void);
void quicksend(char dato);
void quickread(void);

unsigned char uart_data;
int uart_data_ready;

#endif /* UART_H_ */
