/*
 * I2C_Driver.h
 *
 *  Created on: Apr 15, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EEPROM_EXTERNAL_DRIVER_H_
#define HEADERS_EEPROM_EXTERNAL_DRIVER_H_

/*Eeprom Write*/
void EepromWrite(uint8_t Slave_Address,uint16_t Address, uint8_t *pui32DataTx, uint8_t Size);

/*Eeprom Random Read*/
void Ext_EepromRandomRead(uint32_t SlaveAddress,uint16_t Address , uint8_t *DataReceived, uint16_t NumOfBytes);

/*External EEprom*/
void Eeprom_Ext_init();

/*Declarion Of Eeprom External Write*/
void Eeprom_Ext_Write(uint16_t address,uint8_t * data, uint16_t length);

/*Eeprom Ext Read Declaration*/
void Eeprom_Ext_Read(uint16_t address,uint8_t * data, uint16_t length);

#endif /* HEADERS_EEPROM_EXTERNAL_DRIVER_H_ */
