/*
 *  Created on: Feb 19, 2014
 *      Author: Nelson Antonio Pérez Cervantes
 */
#include "derivative.h"
#include "I2C.h"
#include "lcd.h"
unsigned char data_read = 0;

void I2Cinit(void)
{
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB_PCR3 = (PORT_PCR_MUX(2)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK);                                  
	PORTB_PCR2 = (PORT_PCR_MUX(2)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK);
	
	I2C0_C1 = 0x00;
	
	I2C0_C1 |= I2C_C1_IICEN_MASK;
	                                   
	I2C0_F = (I2C_F_MULT(0x00) | I2C_F_ICR(0x1A));
}
void writeI2C(int phy_address, char mem_address, char I2C_data)
{
	I2C0_C1 |= I2C_C1_TX_MASK;
		
	I2C0_C1 |= I2C_C1_MST_MASK;
	while ((I2C0_S & I2C_S_BUSY_MASK)==0);
		
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = 0xA0+(phy_address+phy_address); // PHY ADD
	delay (1000);
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
		
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = mem_address; // MEM ADD
	delay (1000);
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
	
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = I2C_data; // Data
	delay (1000);
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
	delay (1000);
	I2C0_C1 &= ~I2C_C1_MST_MASK;	
	while ((I2C0_S & I2C_S_BUSY_MASK) == 0x00);
}

