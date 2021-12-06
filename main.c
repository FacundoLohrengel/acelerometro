
/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#define direccion_giroscopio 0x1C


uint8_t i2cWrData1 = 0x01; // LE MANDO ESE VALOR PARA QUE ME DEVUElVA
uint8_t i2cWrData2 = 0x02; 
uint8_t i2cWrData3 = 0x03; 
uint8_t i2cWrData4 = 0x04; 
uint8_t i2cWrData5 = 0x05; 
uint8_t i2cWrData6 = 0x06; 
uint8_t i2cRdData[1];

uint8_t buffer[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

char palabra;
unsigned char trama[3]; //envio 5 componentes
uint8_t flag1;
uint8_t flag2;
uint8_t flag3;

void lectura(void) {
    if (trama[0] == 0xFD) {
        flag1 = 1;
        //        UART2_Write(&trama, sizeof (trama));
    }
    if (trama[1] == 0x03) {
        flag2 = 1;
        //        UART2_Write(&trama, sizeof (trama));
    }
    if (trama[2] == 0x41) {
        flag3 = 1;
        //        UART2_Write(&trama, sizeof (trama));
    }
    return;
}

int main(void) {

    /* Initialize all modules */
    SYS_Initialize(NULL);


    UART2_ReadCallbackRegister((UART_CALLBACK) lectura, 0);
    //      UART2_Read(&trama, sizeof (trama));
    while (true) {

        /* Maintain state machines of all polled MPLAB Harmony modules. */
        //        SYS_Tasks();
        // Led


        
        UART2_Read(&trama, sizeof (trama));
        if (flag1 == 1) {
            

            I2C2_WriteRead(direccion_giroscopio, &i2cWrData1, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
                   I2C2_WriteRead(direccion_giroscopio, &i2cWrData2, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
                   I2C2_WriteRead(direccion_giroscopio, &i2cWrData3, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
                   I2C2_WriteRead(direccion_giroscopio, &i2cWrData4, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
                   I2C2_WriteRead(direccion_giroscopio, &i2cWrData5, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
                   I2C2_WriteRead(direccion_giroscopio, &i2cWrData6, 1, i2cRdData, sizeof (i2cRdData));
            UART2_Write(&i2cRdData, sizeof (i2cRdData));
                CORETIMER_DelayMs(10);
            flag1 = 0;
        }

        if (flag2 == 1) {
            UART2_Write(&trama, sizeof (trama));
            flag2 = 0;
        }

        if (flag3 == 1) {
            UART2_Write(&buffer, sizeof (buffer));
            CORETIMER_DelayMs(30);
            UART2_Write(&buffer, sizeof (buffer));
            flag3 = 0;
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */
