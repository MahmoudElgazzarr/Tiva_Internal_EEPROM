#include <stdbool.h>
#include <stdint.h>
#include "I2C_Driver.h"
#include "Eeprom_Internal_Driver.h"
#include <Eeprom_External_Driver.h>
#include "Eep.h"
#include "Ea_Cfg.h"
#include "Ea.h"


uint8_t pui32DataTx[4];
uint8_t pui32DataRx[4];


int main(void)
{
    /*Inalize I2C*/
    I2C_Init();
    /*Inatlize External Eeprom*/
    Eeprom_Ext_init();
    /*Inatilize internal Eeprom*/
    Eeprom_Int_init();
    /*Inalize EEP*/
    Eep_init();
    /*Initalize Ea*/
    Ea_Init();

    /*Inialize Receive Buffer*/
    pui32DataRx[0] = 0;
    pui32DataRx[1] = 0;
    pui32DataRx[2] = 0;
    pui32DataRx[3] = 0;

    /*Put Data To Send*/
    pui32DataTx[0] = 99;
    pui32DataTx[1] = 88;
    pui32DataTx[2] = 77;
    pui32DataTx[3] = 66;

    /*Write To Ea*/
    Ea_Write(Block_ID_1, pui32DataTx);

    /*Read From Eep*/
    Ea_Read(Block_ID_1,Offset_Zero,pui32DataRx,One_Byte);

    while(1)
    {

    }
}
