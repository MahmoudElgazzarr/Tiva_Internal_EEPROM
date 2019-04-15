/*
 * Eeprom_External_Driver.h
 *
 *  Created on: Apr 15, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EEPROM_EXTERNAL_DRIVER_H_
#define HEADERS_EEPROM_EXTERNAL_DRIVER_H_

void Eeprom_Ext_init();

void Eeprom_Ext_Write(uint16_t address,uint32_t * data, uint16_t length);

uint32_t Eeprom_Ext_Read(uint16_t address,uint32_t * data, uint16_t length);

#endif /* HEADERS_EEPROM_EXTERNAL_DRIVER_H_ */
