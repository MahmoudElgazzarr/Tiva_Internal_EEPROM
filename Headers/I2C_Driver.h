/*
 * I2C_Driver.h
 *
 *  Created on: Apr 15, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_I2C_DRIVER_H_
#define HEADERS_I2C_DRIVER_H_

//*****************************************************************************
//
// Number of I2C data packets to send.
//
//*****************************************************************************
#define NUM_I2C_DATA 1
//*****************************************************************************
//
// Set the address for slave module. This is a 7-bit address sent in the
// following format:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
//
// A zero in the "RS" position of the first byte means that the master
// transmits (sends) data to the selected slave, and a one in this position
// means that the master receives data from the slave.
//
//*****************************************************************************
#define SLAVE_ADDRESS 0x22


void I2C_Init();

void I2C_Send(uint8_t Address,uint8_t *pui32DataTx,uint8_t Size);

void I2C_ReceiveDataFromSlave(uint32_t SlaveAddress ,uint8_t *DataReceived , uint16_t NumOfBytes);

void Write_Byte(uint8_t Byte , uint8_t Slave_Address);

void Ext_EepromRandomRead(uint32_t SlaveAddress, uint8_t *DataReceived, uint16_t NumOfBytes);

#endif /* HEADERS_I2C_DRIVER_H_ */
