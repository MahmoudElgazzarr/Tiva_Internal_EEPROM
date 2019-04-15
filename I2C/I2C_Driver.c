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


uint32_t pui32DataTx[NUM_I2C_DATA];
uint32_t pui32DataRx[NUM_I2C_DATA];
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
    UARTprintf("I2C Loopback Example ->");
    UARTprintf("\n   Module = I2C0");
    UARTprintf("\n   Mode = Single Send/Receive");
    UARTprintf("\n   Rate = 100kbps\n\n");
    //
    // Initalize the data to send.
    //
    pui32DataTx[0] = 0;
    pui32DataTx[1] = 0;
    pui32DataTx[2] = 0;

}

void I2C_Send()
{
    /*Set Slave Address*/
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, false);

    //
    // Initalize the receive buffer.
    //
    for (ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        pui32DataRx[ui32Index] = 0;
    }

    //
    // Indicate the direction of the data.
    //
    UARTprintf("Tranferring from: Master -----> Slave\n");

    //
    // Send 3 peices of I2C data from the master to the slave.
    //
    for (ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        //
        // Display the data that the I2C0 master is transferring.
        //
        UARTprintf("  Sending: '%c'  . . .  ", pui32DataTx[ui32Index]);

        //
        // Place the data to be sent in the data register
        //
        I2CMasterDataPut(I2C1_BASE, pui32DataTx[ui32Index]);

        //
        // Initiate send of data from the master.  Since the loopback
        // mode is enabled, the master and slave units are connected
        // allowing us to receive the same data that we sent out.
        //
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    }
}

uint32_t I2C_Receive()
{
    //
    // Reset receive buffer.
    //
    for (ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        pui32DataRx[ui32Index] = 0;
    }

    //
    // Indicate the direction of the data.
    //
    UARTprintf("\n\nTranferring from: Slave -> Master\n");

    //
    // Modifiy the data direction to true, so that seeing the address will
    // indicate that the I2C Master is initiating a read from the slave.
    //
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, true);

    //
    // Do a dummy receive to make sure you don't get junk on the first receive.
    //
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //
    // Dummy acknowledge and wait for the receive request from the master.
    // This is done to clear any flags that should not be set.
    //
    while (!(I2CSlaveStatus(I2C1_BASE) & I2C_SLAVE_ACT_TREQ))
    {
    }

    for (ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        //
        // Display the data that I2C0 slave module is transferring.
        //
        UARTprintf("  Sending: '%c'  . . .  ", pui32DataTx[ui32Index]);

        //
        // Place the data to be sent in the data register
        //
        I2CSlaveDataPut(I2C1_BASE, pui32DataTx[ui32Index]);

        //
        // Tell the master to read data.
        //
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //
        // Wait until the slave is done sending data.
        //
        while (!(I2CSlaveStatus(I2C1_BASE) & I2C_SLAVE_ACT_TREQ))
        {
        }

        //
        // Read the data from the master.
        //
        pui32DataRx[ui32Index] = I2CMasterDataGet(I2C1_BASE);

        //
        // Display the data that the slave has received.
        //
        UARTprintf("Received: '%c'\n", pui32DataRx[ui32Index]);
    }

    //
    // Tell the user that the test is done.
    //
    UARTprintf("\nDone.\n\n");

    //
    // Return no errors
    //
    return (0);
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
