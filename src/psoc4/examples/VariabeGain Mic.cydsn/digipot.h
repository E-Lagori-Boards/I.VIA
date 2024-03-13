#ifndef DIGIPOT_H
#define DIGIPOT_H
    
#include "project.h"

#define TX_SIZE   (2u)
#define RX_SIZE   (1u) 
    
#define BUFFER_SIZE   (8u)


unsigned addr,d_bit;

uint8 txbuffer[BUFFER_SIZE];
uint8 rxbuffer[BUFFER_SIZE];

uint32 sendi2cdata();
uint32 receivei2cdata();
uint32 Command16();
uint32 check_i2c(int);
uint32 read_data;
uint32 chgBoardaddr(int);
uint32 Write_RDAC(uint8,int);
uint32 Readback_RDAC(uint8); 
uint8 StoreValue(uint8);
uint8 RestoreValue(uint8); 

uint32 chgBoardaddr(int address){
    switch (address){
        case 11: addr = 0b0100000;break;
        case 21: addr = 0b0100010;break;
        case 01: addr = 0b0100011;break;
        case 12: addr = 0b0101000;break;
        case 22: addr = 0b0101010;break;
        case 02: addr = 0b0101011;break;
        case 10: addr = 0b0101100;break;
        case 20: addr = 0b0101110;break;
        case 00: addr = 0b0101111;break;
        default: addr=0;break;
        }
    return addr;
}

uint32 sendi2cdata(){
    (void) I2CM_I2CMasterClearStatus();
    if(I2CM_I2C_MSTR_NO_ERROR == I2CM_I2CMasterWriteBuf(addr,
                                    txbuffer,TX_SIZE,
                                    I2CM_I2C_MODE_COMPLETE_XFER))
    {
        while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT))
        {
            /* Wait */
        }
        
        if (0u != (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_ERR_XFER))
        {
            return 0;
        }
    }
    return 1;
}

uint32 receivei2cdata(){
    (void) I2CM_I2CMasterClearStatus();
    if(I2CM_I2C_MSTR_NO_ERROR ==  I2CM_I2CMasterReadBuf(addr,
                                    rxbuffer,RX_SIZE,
                                    I2CM_I2C_MODE_COMPLETE_XFER))
    {
        while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_RD_CMPLT))
        {
            /* Wait */
        }

        if (0u != (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
        {
            return 0;
        }
    }
    uint8 Digipot_read_bit = rxbuffer[0];
    return Digipot_read_bit;
    }

uint32 Command16(){
    txbuffer[0] = 0B11010000;
    txbuffer[1] = 0B00000011;
    sendi2cdata();  
    return check_i2c(2);
    }

uint32 check_i2c(int data){
    txbuffer[0] = 0b00110000;
    txbuffer[1] = data;
    sendi2cdata();
    receivei2cdata();
    read_data = ((receivei2cdata() == 19)||(receivei2cdata() == 3))? 1:0;
    return read_data;
    }
        
uint32 Write_RDAC(uint8 RDACno, int D_set){
    Command16();
    txbuffer[0] = (RDACno)?0b00010001:0b00010000;
    txbuffer[1] = (D_set);
    return sendi2cdata();
    }

uint32 Readback_RDAC(uint8 RDACno){
    txbuffer[0] = (RDACno)?0b00110001:0b00110000;
    txbuffer[1] = 3 ;
    sendi2cdata();
    read_data = receivei2cdata();
    return read_data;
    }

uint8 StoreValue(uint8 RDACno){
    Command16();
    txbuffer[1] = 1;
    txbuffer[0] = (RDACno)?0b01110001:0b01110000;
    sendi2cdata();
    return 0;
    }

uint8 RestoreValue (uint8_t RDACno){   
    Command16();
    txbuffer[1] = 0;
    txbuffer[0] = (RDACno)?0b01110001:0b01110000;
    sendi2cdata();
    return 0;
    }

    #endif