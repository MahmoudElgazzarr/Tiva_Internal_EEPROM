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
#include "I2C_Driver.h"

uint32_t ui32Index;

void I2C_Init()
{

    InitConsole();
    //
    // The I2C0 peripheral must be enabled before use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    //
    // For this example I2C0 is used with PortB[3:2].  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.  GPIO port B needs to be enabled so these pins can
    // be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA6_I2C1SCL); /*Clock*/
    GPIOPinConfigure(GPIO_PA7_I2C1SDA); /*Data*/

    //
    // Select the I2C function for these pins.  This function will also
    // configure the GPIO pins pins for I2C operation, setting them to
    // open-drain operation with weak pull-ups.  Consult the data sheet
    // to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    //
    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.  For this example we will use a data rate of 100kbps.
    //

    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
    //
    // Enable the I2C0 slave module. This module is enabled only for testing
    // purposes.  It does not need to be enabled for proper operation of the
    // I2Cx master module.
    //
    //
    // Display the example setup on the console.
    //
    UARTprintf("I2C Init");
    UARTprintf("\n   Module = I2C1");
    UARTprintf("\n   Mode = Send");
    UARTprintf("\n   Rate = 100kbps\n\n");

}

void I2C_Send(uint8_t Address, uint8_t *pui32DataTx, uint8_t Size)
{
    /*Set Slave Address*/
    I2CMasterSlaveAddrSet(I2C1_BASE, Address, false);

    // Indicate the direction of the data.
    UARTprintf("Tranferring from: Master -----> Slave\n");

    /*Send Multiple Bytes*/
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

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

void I2C_ReceiveDataFromSlave(uint32_t SlaveAddress, uint8_t *DataReceived, uint16_t NumOfBytes)
{
    uint16_t Index;
    /* Set Address to the device you want to read from */
    I2CMasterSlaveAddrSet(I2C1_BASE, SlaveAddress, true);

    /* set Master to Start read from slave  */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    /* Wait until master complete Reception */
    while (I2CMasterBusy(I2C1_BASE));

    for (Index = 0; Index < NumOfBytes; Index++)
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
}
void Ext_EepromRandomRead(uint32_t SlaveAddress, uint8_t *DataReceived, uint16_t NumOfBytes)
{
    uint16_t Index;
        /* Set Address to the device you want to read from */
        /*Send Dummy Byte*/
        I2CMasterSlaveAddrSet(I2C1_BASE, SlaveAddress, false);

        /*Send Single Dummy Byte*/
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        /*Put Dummy Data & End Send*/
        I2CMasterDataPut(I2C1_BASE,0x00);

        /* Wait until master complete Reception */
          while (I2CMasterBusy(I2C1_BASE));

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
}

void Write_Byte(uint8_t Byte , uint8_t Slave_Address)
{
    /*Set Slave Address*/
    I2CMasterSlaveAddrSet(I2C1_BASE, Slave_Address, false);
}

void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
