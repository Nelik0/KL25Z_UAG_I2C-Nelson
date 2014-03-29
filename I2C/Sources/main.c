/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "lcd.h"
#include "I2C.h"
unsigned char ready = 0;
int read = 0;
unsigned char I2C_CycleRead(unsigned char byte_pending);
int main(void)

{
	 cfgPortsLCD();
	 I2Cinit();
	for(;;)
	{
		if (ready == 0)
		{
			//writeI2C(0x00,0x00,0xDD);
			readI2C(0x00,0x00);
			
		}
	}
	
	return 0;
}
void readI2C(int read_p_address, char read_mem_address)
{
	
	I2C0_C1 |= I2C_C1_TX_MASK;
	
	I2C0_C1 |= I2C_C1_MST_MASK;
	while ((I2C0_S & I2C_S_BUSY_MASK)==0);
	
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = 0xA0+(read_p_address+read_p_address); // PHY ADD
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
	
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = read_mem_address; // MEM ADD
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
	
	I2C0_C1 |= I2C_C1_RSTA_MASK;
	while ((I2C0_S & I2C_S_BUSY_MASK)==0);
	
	while ((I2C0_S & I2C_S_TCF_MASK)==0);
	I2C0_D = 0xA0+(read_p_address+read_p_address)+1; // PHY ADD
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0x00);
	I2C0_S |= I2C_S_IICIF_MASK;
	
	read = I2C_CycleRead(0);
	
	I2C0_C1 &= ~I2C_C1_MST_MASK;
	
	while ((I2C0_S & I2C_S_BUSY_MASK) == 0x00);
}
unsigned char I2C_CycleRead(unsigned char byte_pending)
{
	unsigned char byte_read=0;
	
	while ((I2C0_S & I2C_S_TCF_MASK) == 0);
	I2C0_C1 &= ~I2C_C1_TX_MASK ; 
	if(byte_pending==1) {I2C0_C1 &= ~I2C_C1_TXAK_MASK ;}
	if(byte_pending==0) {I2C0_C1 |=  I2C_C1_TXAK_MASK ;}
	byte_read = I2C0_D;
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0);
	while ((I2C0_S & I2C_S_TCF_MASK) == 0);
	//I2C0_C1 |= I2C_C1_TX_MASK ; 
	byte_read = I2C0_D;
	while ((I2C0_S & I2C_S_IICIF_MASK) == 0);
	while ((I2C0_S & I2C_S_TCF_MASK) == 0);
	I2C0_S |= I2C_S_IICIF_MASK ;

	return byte_read;
}
