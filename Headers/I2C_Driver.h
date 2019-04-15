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

extern uint32_t pui32DataTx[NUM_I2C_DATA];
extern uint32_t pui32DataRx[NUM_I2C_DATA];

void I2C_Init();

void I2C_Send();

uint32_t I2C_Receive();

#endif /* HEADERS_I2C_DRIVER_H_ */
