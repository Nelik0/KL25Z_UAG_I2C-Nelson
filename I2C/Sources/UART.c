/*
 *  Created on: Feb 19, 2014
 *      Author: Nelson Antonio Pérez Cervantes
 */
#include "derivative.h"
#include "UART.h"

void UARTinit(void)
{
SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
 SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;                                                   
	
 /* PORTA_PCR1: ISF=0,MUX=2 */
 PORTA_PCR1 |= (PORT_PCR_MUX(2));
 
 /* PORTA_PCR2: ISF=0,MUX=2 */
 PORTA_PCR2 |= (PORT_PCR_MUX(2));

 /* Disable TX & RX while we configure settings */
 UART0_C2 &= ~(UART0_C2_TE_MASK); //disable transmitter
 UART0_C2 &= ~(UART0_C2_RE_MASK); //disable receiver
 
 /* UART0_C1: LOOPS=0,DOZEEN=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
 UART0_C1 = 0x00U; /* Set the C1 register */
 /* UART0_C3: R8T9=0,R9T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
 UART0_C3 = 0x00U; /* Set the C3 register */
 /* UART0_S2: LBKDIF=0,RXEDGIF=0,MSBF=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
 UART0_S2 = 0x00U; /* Set the S2 register */
 
 SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); //set clock source to be from PLL/FLL
 SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
 unsigned SBR = 546;//137; //Set the baud rate register, SBR = 137
 UART0_BDH |= (~UART0_BDH_SBR_MASK) | SBR >> 8;
 UART0_BDL |= (~UART0_BDL_SBR_MASK) | SBR;
 
 char OSR = 3; //set the oversampling ratio to option #3 = 4x
 UART0_C4 &= (~UART0_C4_OSR_MASK) | OSR;
 
 /*
 * Target Baud rate = 38400 9600
 *
 * Baud rate = baud clock / ((OSR+1) * SBR)
 * baud clock = FLL/PLL = 20.97152MHz  32kHZ
 * OSR = 3
 * SBR = 137 //546
 * Resulting Baud rate = 20.97152MHz / ((3 + 1) * 546) = 9600
 */
 
 UART0_C5 |= UART0_C5_BOTHEDGE_MASK; //enable sampling on both edges of the clock
 UART0_C2 |= UART0_C2_TE_MASK; //enable transmitter
 UART0_C2 |= UART0_C2_RE_MASK; //enable receiver
	
 uart_data_ready = 0;
 uart_data = 0;
}

void quicksend(char dato)
{
	UART0_D = dato;
	while ((UART0_S1 & 0x40) == 0);
}
void quickread(void)
{
	if(UART0_S1 & 0x20)
	{
		uart_data = UART0_D;
		uart_data_ready = 1;
	}
}
