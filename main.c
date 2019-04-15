

/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#include <stdint.h>
#include "Eeprom_Internal_Driver.h"

uint32_t pui32Data[2]={0x12345678,0x56789abc};
uint32_t pui32Read[2]={0};


int main(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); /* Enable the GPIOF port that is used for the on-board Leds . */

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); /* Wait until Peripheral is Stable to use */

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2); /* Set Pin 1,2 in PortF to Output */

    /* Initialize EEPROM */
    Eeprom_Int_init();

    Eeprom_Int_Write(0x400,pui32Data,8);
    Eeprom_Int_Read(0x400,pui32Read,8);

    /* Test if Data Read Correctly then Turn on led*/
    if(pui32Read[0] == 0x12345678)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    }

    while(1)
    {

    }
}
