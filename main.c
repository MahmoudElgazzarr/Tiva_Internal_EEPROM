#include <stdbool.h>
#include <stdint.h>
#include "I2C_Driver.h"
#include <Eeprom_External_Driver.h>


uint8_t pui32DataTx[3];
uint8_t pui32DataRx[2];


int main(void)
{
    /*Inalize I2C*/
    I2C_Init();

    pui32DataRx[0] = 0;
    pui32DataRx[1] = 0;
    pui32DataRx[2] = 0;

    pui32DataTx[0] = 99;
    pui32DataTx[1] = 88;
    pui32DataTx[2] = 77;

    /*Write To External Eeprom*/
    Eeprom_Ext_Write(0x0002,pui32DataTx,3);

    /*Read From External Eeprom*/
    Eeprom_Ext_Read(0x0002,pui32DataRx,3);

    //I2C_ReceiveDataFromSlave(0x50,pui32DataRx,3);
    while(1)
    {

    }
}
