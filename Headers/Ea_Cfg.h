/*
 * Ea_Cfg.h
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EA_CFG_H_
#define HEADERS_EA_CFG_H_


#define Num_of_Blocks 2

typedef struct Block_S
{
    uint16_t Block_ID;
    uint16_t Legth_In_Bytes;
    uint16_t *Start_Address;
}Block_S_T;


enum Length_In_Bytes
{
    One_Byte,
    Two_Bytes,
    Three_Bytes,
    Four_Bytes,
    Five_Bytes,
};


#endif /* HEADERS_EA_CFG_H_ */
