/*
 *  Created on: Feb 19, 2014
 *      Author: Nelson Antonio Pérez Cervantes
 */
#include "derivative.h"
#include "lcd.h"

void cfgPortsLCD(void) 
{ 
    //Turn on clock for portD and portB 
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; 
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
    //Also, we can use predefined masks created by freescale, such as: 
    //SIM_SCGC5_PORTB_MASK; 
      
    /* Set pins of PORTD as GPIO */
	
	
    PORTC_PCR0=(PORT_PCR_MUX(1)); 	//D0
    PORTE_PCR5=(PORT_PCR_MUX(1));	//D1
    PORTD_PCR2=(PORT_PCR_MUX(1)); 	//D2
    PORTD_PCR3=(PORT_PCR_MUX(1)); 	//D3
    PORTD_PCR4=(PORT_PCR_MUX(1)); 	//D4
    PORTD_PCR5=(PORT_PCR_MUX(1)); 	//D5
    PORTE_PCR0=(PORT_PCR_MUX(1)); 	//D6
    PORTE_PCR1=(PORT_PCR_MUX(1));	//D7
	/* Set pins of PORTB as GPIO */
    PORTB_PCR0=(PORT_PCR_MUX(1)); 	//E
    PORTB_PCR1=(PORT_PCR_MUX(1)); 	//RS
      
    //Reasure first PortB and PortC value 
	GPIOB_PDOR = 0x00;
    GPIOD_PDOR = 0x00;
    GPIOE_PDOR = 0x00;
	GPIOC_PDOR = 0x00;
    //Configure PortC as outputs 
    GPIOD_PDDR |= 0xFC; 
    GPIOB_PDDR = 0xFF; 
    GPIOE_PDDR |= 0x23;
	GPIOC_PDDR |= 0x01;
	initLCD();

} 
void delay (long time) 
{  
    x = time; 
    while(x>0) 
    { 
    x--; 
    } 
} 
  
void initLCD(void) 
{ 
    delay(ntime_15msec); 
    //Commands = {0x38, 0x38, 0x38, 0x0C, 0x01}; 
    sendCode(nIns, 0x38); 
	sendCode(nIns, 0x38); 
	sendCode(nIns, 0x38); 
	sendCode(nIns, 0x0C); 
	sendCode(nIns, 0x01); 
} 
  
void sendCode(int Code, int PortData) 
{   
    PortRS_0; 
    PortEnable_0; 
      
    PortD_LCD = (PortData & 0x3C);
	GPIOC_PDOR = (PortData & 0x01);
    PortE_LCD = (((PortData & 0x02)/0x02)*32)+(((PortData & 0x40)/0x40)*1)+(((PortData & 0x80)/0x80)*2);
      
    if (Code == nIns) 
    { 
        PortRS_0; 
		PortEnable_1;
		delay(ntime_40usec);
		PortEnable_0;
		PortRS_0;
		delay(ntime_15msec);
    } 
    else if (Code == nData) 
    { 
        PortRS_1; 
		PortEnable_1; 
        delay(ntime_40usec); 
        PortEnable_0; 
        PortRS_0; 
		delay(ntime_15msec);
	}
} 
void editChar (int position)
{
	switch (position)
	{
		case 0x00:
		sendCode(nIns,0x40);
		break;
		case 0x01:
		sendCode(nIns,0x48);
		break;
		case 0x02:
		sendCode(nIns,0x50);
		break;
		case 0x03:
		sendCode(nIns,0x58);
		break;
		case 0x04:
		sendCode(nIns,0x60);
		break;
		case 0x05:
		sendCode(nIns,0x68);
		break;
		case 0x06:
		sendCode(nIns,0x70);
		break;
		case 0x07:
		sendCode(nIns,0x48);
		break;
		default:
		sendCode(nIns,0x40);
		break;
	}
}

void BCD(int valor)	
{
	cen = valor / 100;
	r = valor % 100;
	dec = r / 10;
	r = r % 10;
	uni = r;
}

