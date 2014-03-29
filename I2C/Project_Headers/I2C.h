//I2C.h

#ifndef I2C_H_
#define GPIO_PIN_MASK 0x1Fu 
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))

void writeI2C(int phy_address, char mem_address, char I2C_data);
void I2Cinit(void);
void readI2C(int read_p_address, char read_mem_address); 
#endif /* I2C_H_ */
