#include <stdbool.h>
#include <stdint.h>
#include "I2C_Driver.h"
#include "Eeprom_Internal_Driver.h"
#include <Eeprom_External_Driver.h>
#include "Eep.h"
#include "Ea_Cfg.h"
#include "Ea.h"

typedef struct Sensor
{
    uint32_t timestamp;
    uint16_t reading;
    uint8_t status;
}Sensor_T;

typedef struct Error
{
    uint32_t timestamp;
    uint8_t code;
    uint8_t sensor;
    uint8_t reading;
}Error_T;

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

    /*Create 3 Sensor Elements*/
    Sensor_T Sensor1,Sensor2,Sensor3;
    /*Create 3 Error Elements*/
    Error_T Error1,Error2,Error3;

    /*Intalize Structure To Read*/
    Sensor_T Sensor1_R;

    /*Init Sensor1 Data*/
    Sensor1.reading = 99;
    Sensor1.status = 88;
    Sensor1.timestamp = 77;

    /*Init Sensor 2 Data*/
    Sensor2.reading = 99;
    Sensor2.status = 88;
    Sensor2.timestamp =77;

    /*Write To Ea First Sensor Data*/
    Ea_Write(Block_ID_1,(uint8_t *)&Sensor2);
    /*Write To Ea Second Sensor Data*/
    Ea_Write(Block_ID_2,(uint8_t *)&Sensor2);
    /*Write To Ea Third Sensor Data*/
    Ea_Write(Block_ID_3,(uint8_t *)&Sensor3);

    /*Read From Ea Sensor 1*/
    Ea_Read(Block_ID_1, Offset_Zero,(uint8_t *)&Sensor1_R, Eight_Bytes);

    /*Read From Ea Sensor 2*/
    Ea_Read(Block_ID_2, Offset_Zero,(uint8_t *)&Sensor2, Eight_Bytes);

    /*Read From Ea Sensor 3*/
    Ea_Read(Block_ID_3, Offset_Zero,(uint8_t *)&Sensor3, Eight_Bytes);

    while (1)
    {

    }
}
