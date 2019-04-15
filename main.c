#include <stdbool.h>
#include <stdint.h>
#include "I2C_Driver.h"

uint8_t pui32DataTx[3];
uint8_t pui32DataRx[2];



int main(void)
{
    pui32DataRx[0] = 0;
    pui32DataRx[1] = 0;
    pui32DataRx[2] = 0;
    I2C_Init();
    pui32DataTx[0] = 0x00;
    pui32DataTx[1] = 0x01;
    pui32DataTx[1] = 0x55;
    Ext_EepromRandomRead(0x50,pui32DataRx,1);
    //I2C_Send(0x50,pui32DataTx,3);
    //I2C_ReceiveDataFromSlave(0x50,pui32DataRx,3);
    while(1)
    {

    }
}
