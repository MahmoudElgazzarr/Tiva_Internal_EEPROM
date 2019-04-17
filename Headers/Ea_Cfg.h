/*
 * Ea_Cfg.h
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_EA_CFG_H_
#define HEADERS_EA_CFG_H_


#define Num_of_Blocks 1

typedef struct Block_S
{
    uint16_t Block_ID;
    uint16_t Legth_In_Bytes;
    uint16_t *Start_Address;
}Block_S_T;


enum Length_In_Bytes
{
    One_Byte = 1,
    Two_Bytes,
    Three_Bytes,
    Four_Bytes,
    Five_Bytes,
};
enum Block_IDs
{
    Block_ID_1=1,
    Block_ID_2,
    Block_ID_3,
    Block_ID_4,
};

enum Offset
{
    Offset_Zero,
    Offset_One,
    Offset_Two,
};


#endif /* HEADERS_EA_CFG_H_ */
