/*
 * I2C_Driver.c
 *
 *  Created on: Apr 15, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Eeprom_External_Driver.h"

uint32_t ui32Index;

void EepromWrite(uint8_t Slave_Address,uint16_t Address, uint8_t *pui32DataTx, uint8_t Size)
{
    /*Set Most Siginifcant Address*/
    I2CMasterSlaveAddrSet(I2C1_BASE, Slave_Address , false);

    // Indicate the direction of the data.
    UARTprintf("Tranferring from: Master -----> Slave\n");

    /*Put Most Siginificant Address*/
    I2CMasterDataPut(I2C1_BASE,(uint8_t)(Address>>8));

    /*Start Sending*/
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    /*Wait Until Receive Ack*/
    while (I2CMasterBusy(I2C1_BASE));

    /*Put Least Significant Address*/
    I2CMasterDataPut(I2C1_BASE,(uint8_t)Address);

    /*continue Sending*/
    I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_CONT);

    /*Send 3 peices of I2C data from the master to the slave*/
    for (ui32Index = 0; ui32Index < Size; ui32Index++)
    {
        /*Display the data that the I2C1 master is transferring*/
        UARTprintf("  Sending: '%c'  . . . \n", pui32DataTx[ui32Index]);

        /* Place the data to be sent in the data register */
        I2CMasterDataPut(I2C1_BASE, pui32DataTx[ui32Index]);

        I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_CONT);

        /* Wait until master complete Reception of Ack */
        while (I2CMasterBusy(I2C1_BASE));
    }
    /* Send Negative Ack To Slave That Reception is complete */
     I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
}

void Ext_EepromRandomRead(uint32_t SlaveAddress,uint16_t Address , uint8_t *DataReceived, uint16_t NumOfBytes)
{
        uint16_t Index;
        /* Set Address to the device you want to read from */
        I2CMasterSlaveAddrSet(I2C1_BASE, SlaveAddress, false);

        /*Put Most Significant Address*/
        I2CMasterDataPut(I2C1_BASE,(uint8_t)(Address>>8));

        /*Send Two Bytes*/
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        /* Wait until master complete Reception */
        while (I2CMasterBusy(I2C1_BASE));

        /*Put Least Significant Address*/
        I2CMasterDataPut(I2C1_BASE,(uint8_t)(Address));

        /*Continue Reading*/
        I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_CONT);

        /* Wait until master complete Reception */
        while (I2CMasterBusy(I2C1_BASE));

        /* Set Address to the device you want to read from */
        I2CMasterSlaveAddrSet(I2C1_BASE, SlaveAddress, true);

        /* set Master to Start read from slave  */
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

        /* Wait until master complete Reception */
        while (I2CMasterBusy(I2C1_BASE));

        for (Index = 0; Index < NumOfBytes ; Index++)
        {
            /* Store Data in Buffer */
            DataReceived[Index] = I2CMasterDataGet(I2C1_BASE);

            /* Send To Slave To Continiue Sending*/
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

            /* Wait until master complete Reception */
            while (I2CMasterBusy(I2C1_BASE));
        }
        /* Send Finish Ack */
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        while (I2CMasterBusy(I2C1_BASE));
}

void Eeprom_Ext_init()
{

}

void Eeprom_Ext_Write(uint16_t address,uint8_t * data, uint16_t length)
{
    EepromWrite(SLAVE_ADDRESS,address,data,length);
}
void Eeprom_Ext_Read(uint16_t address,uint8_t * data, uint16_t length)
{
    /*Write To External EEPROM*/
    Ext_EepromRandomRead(SLAVE_ADDRESS,address,data, length);
}
