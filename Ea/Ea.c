/*,
 * Ea.c
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#include <stdint.h>
#include "Eep_Cfg.h"
#include "Eep.h"
#include "Ea_Cfg.h"
#include "Ea.h"


/*Extern of Arr Of Blocks*/
extern Block_S_T Block_Arr[Num_of_Blocks];

/*Init The Ea Module*/
void Ea_Init()
{

}
/*Function That Abstracts Address Of The Block To Read To Eeprom*/
void Ea_Read(uint16_t blocknumber, uint16_t blockoffset, uint8_t * data, uint16_t length)
{
    uint8_t index;
    uint8_t Block_Index_In_Arr;
    for (index=0; index<Num_of_Blocks; index++)
       {
           if(Block_Arr[index].Block_ID == blocknumber )
           {
               Block_Index_In_Arr = index;
               break;
           }
       }
    if(length <= Block_Arr[Block_Index_In_Arr].Legth_In_Bytes)
    {
        Eep_Read(*(Block_Arr[Block_Index_In_Arr].Start_Address) + blockoffset ,data,length);
    }
    else
    {
        /*Return Error*/
    }
}
/*Function That Abstracts Address Of The Block To Write To Eeprom*/
void Ea_Write(uint16_t blocknumber, uint8_t * data)
{
    uint8_t index;
    uint8_t Block_Index_In_Arr;
    for (index=0; index<Num_of_Blocks; index++)
    {
        if(Block_Arr[index].Block_ID == blocknumber )
        {
            Block_Index_In_Arr = index;
            break;
        }
    }
    Eep_Write(*(Block_Arr[Block_Index_In_Arr].Start_Address),data, Block_Arr[Block_Index_In_Arr].Legth_In_Bytes);
}
