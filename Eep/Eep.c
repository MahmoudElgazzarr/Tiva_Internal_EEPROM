/*
 * Eep.c
 *
 *  Created on: Apr 16, 2019
 *      Author: AVE-LAP-040
 */

#include <stdint.h>
#include "Eeprom_External_Driver.h"
#include "Eeprom_Internal_Driver.h"
#include "Eep_Cfg.h"
#include "Eep.h"

void Eep_init()
{

}
void Eep_Write(uint16_t address,uint8_t * data, uint16_t length)
{
    if( (address >= External_Eeprom_Start_Address) && (address <= External_Eeprom_End_Address ))
    {
        /*Write To External EEprom*/
        Eeprom_Ext_Write(address,data,length);
    }
    else if((address >= (Internal_Eeprom_Start_Address + External_Eeprom_End_Address)) && (address <= (Internal_Eeprom_End_Address+ External_Eeprom_End_Address)))
    {
        /*Write To Internal Eeprom*/
        Eeprom_Int_Write(address - External_Eeprom_End_Address ,data,length);
    }
    else
    {
        /*return Error*/
    }
}

void Eep_Read(uint16_t address,uint8_t * data, uint16_t length)
{
    if( (address >= External_Eeprom_Start_Address) && (address <= External_Eeprom_End_Address ) )
    {
        /*Read From External Eeprom*/
        Eeprom_Ext_Read(address,data,length);
    }
    else if((address >= (Internal_Eeprom_Start_Address + External_Eeprom_End_Address)) && (address <= (Internal_Eeprom_End_Address+ External_Eeprom_End_Address)))
    {
        /*Read From Internal Eeprom*/
        Eeprom_Int_Read(address,data,length);
    }
    else
    {
        /*return Error*/
    }
}
