#include <stdint.h>
#include "eeprom_pb.h"
#include "Eeprom_Internal_Driver_Cfg.h"
#include "Eeprom_Internal_Driver.h"

void Eeprom_Int_init()
{
    /*Inatialize EEPROM*/
    EEPROMPBInit(ui32Start, ui32Size);
}

uint8_t Eeprom_Int_Write(uint16_t address, uint32_t * data, uint16_t length)
{
    /* Writes data to the EEPROM. and return status*/
    return EEPROMProgram(data, address, length);
}

uint32_t Eeprom_Int_Read(uint16_t address, uint32_t * data, uint16_t length)
{
    /* Reads data from the EEPROM. */
    EEPROMRead(data, address, length);
}
