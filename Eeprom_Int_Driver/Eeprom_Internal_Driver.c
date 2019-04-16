#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/eeprom.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "utils/eeprom_pb.h"
#include "Eeprom_Internal_Driver_Cfg.h"
#include "Eeprom_Internal_Driver.h"

/*Inatialize EEPROM*/
uint32_t Eeprom_Int_init(void)
{
    uint32_t ui32EEPROMInit;

    /* Enable the EEPROM module. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    /* Wait for the EEPROM module to be ready. */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0));

    /* Wait for the EEPROM Initialization to complete */
    ui32EEPROMInit = EEPROMInit();

    /* Return EEPROM Initialization State */
    return ui32EEPROMInit;
}

uint8_t Eeprom_Int_Write(uint16_t address, uint8_t * data, uint8_t length)
{
    /* Writes data to the EEPROM. and return status*/
    return EEPROMProgram((uint32_t *) data, (uint32_t) address,(uint32_t) length);
}

void Eeprom_Int_Read(uint16_t address, uint8_t * data, uint8_t length)
{
    /* Reads data from the EEPROM. */
    EEPROMRead((uint32_t *) data, (uint32_t) address, (uint32_t) length);
}
