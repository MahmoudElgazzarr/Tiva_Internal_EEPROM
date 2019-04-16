/*
 * Ea.h
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EA_H_
#define HEADERS_EA_H_

void Ea_Init();
void Ea_Read(uint16_t blocknumber, uint16_t blockoffset, uint8_t * data, uint16_t length);
void Ea_Write(uint16_t blocknumber, uint8_t * data);



#endif /* HEADERS_EA_H_ */
