/*
 * Eep.h
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EEP_H_
#define HEADERS_EEP_H_

void Eep_init();
void Eep_Write(uint16_t address,uint8_t * data, uint16_t length);
void Eep_Read(uint16_t address,uint8_t * data, uint16_t length);


#endif /* HEADERS_EEP_H_ */
