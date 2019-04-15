/*
 * Eeprom_Internal_Driver.h
 *
 *  Created on: Apr 15, 2019
 *      Author: AVE-LAP-040
 */

//*****************************************************************************
//
// eeprom_pb.h - Prototypes for the EEPROM parameter block functions.
//
// Copyright (c) 2014-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the Tiva Utility Library.
//
//*****************************************************************************

#ifndef HEADERS_EEPROM_INTERNAL_DRIVER_H_
#define HEADERS_EEPROM_INTERNAL_DRIVER_H_

void Eeprom_Int_init();
uint8_t Eeprom_Int_Write(uint16_t address,uint32_t * data, uint16_t length);
uint32_t Eeprom_Int_Read(uint16_t address,uint32_t * data, uint16_t length);

#endif /* HEADERS_EEPROM_INTERNAL_DRIVER_H_ */
