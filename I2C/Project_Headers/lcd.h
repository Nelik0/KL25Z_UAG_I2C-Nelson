//LCD.h

#ifndef lcd_H_
#define GPIO_PIN_MASK 0x1Fu 
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))
#define PortD_LCD         GPIOD_PDOR 
#define PortE_LCD         GPIOE_PDOR 
#define PortEnable_1    GPIOB_PDOR |= 0x01 
#define PortEnable_0    GPIOB_PDOR &= 0xFE 
#define PortRS_1        GPIOB_PDOR |= 0x02 
#define PortRS_0        GPIOB_PDOR &= 0xFD 
#define ntime_1seg      420000
#define ntime_15msec    3500
#define ntime_40usec    35  
#define nIns    0 
#define nData   1

void cfgPortsLCD(void); 
void delay(long time); 
void initLCD(void); 
void sendCode(int Code, int PortData);
int x,i;
void editChar (int position);
void BCD(int valor);
int uni, dec, cen, r;
int escritura;
int pos;
#endif /* lcd_H_ */
