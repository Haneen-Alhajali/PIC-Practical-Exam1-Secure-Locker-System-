/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include <math.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
char temp;
int c[3] = {0}; // Received number from PC
int c2[3] = {0}; // User guessed number
int n = 0;
int dig = 0;
int attempts = 0;
bool equal = true;
int success = 0;
int result;

int FSarray[4] = {0x08, 0x01, 0x04, 0x02};

void APP_Tasks(void) {

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized) {
                PORTG = 0x0000;
                DRV_TMR0_Start();
                appData.flageled = 0;

                appData.state = RX;

            }
            break;
        }

        case enter:
        {
            //    if (attempts == 0) {
            //        PORTG = 0x1000;
            //        int i = 0;
            //        for (; i < 1000000; i++);
            //    }
            //    if (attempts == 1) {
            //        PORTG = 0x3000;
            //        int i = 0;
            //        for (; i < 1000000; i++);
            //    }
            //         if (attempts == 2) {
            //        PORTG = 0x7000;
            //        int i = 0;
            //        for (; i < 1000000; i++);
            //          appData.state = check;
            //        break;
            //    }
            //    if (dig == 3) {

            //        attempts++;
            //        appData.state = check;
            //        break;
            //    }

            if (attempts == 0) {
                PORTG = 0x1000;
                int i = 0;
                for (; i < 1000000; i++);
            }
            //                                    appData.flageled = 0; 
            //                                    DRV_TMR0_Close();

            if (dig < 3) {

                int i = 0;
                PORTF = 0x1030;
                PORTE = 0x0200;
                PORTA = 0x0032;
                for (; i < 10000000; i++);
                if (PORTAbits.RA5 == 0) {

                    DRV_USART0_WriteByte('1');
                    c2[dig] = 1;
                    dig++;



                } else if (PORTAbits.RA4 == 0) {
                    DRV_USART0_WriteByte('4');
                    c2[dig] = 4;

                    dig++;

                } else if (PORTAbits.RA1 == 0) {
                    DRV_USART0_WriteByte('7');
                    c2[dig] = 7;

                    dig++;

                } else if (PORTEbits.RE9 == 0) {
                    DRV_USART0_WriteByte('0');
                    c2[dig] = 0;

                    dig++;

                }
                PORTF = 0x3020;
                PORTE = 0x0200;
                PORTA = 0x0032;
                for (i = 0; i < 1000; i++);

                if (PORTAbits.RA4 == 0) {
                    DRV_USART0_WriteByte('5');
                    c2[dig] = 5;

                    dig++;

                } else if (PORTAbits.RA5 == 0) {
                    DRV_USART0_WriteByte('2');
                    c2[dig] = 2;

                    dig++;

                } else if (PORTAbits.RA1 == 0) {
                    DRV_USART0_WriteByte('8');
                    c2[dig] = 8;

                    dig++;

                } else if (PORTEbits.RE9 == 0) {
                    DRV_USART0_WriteByte('f');
                }

                PORTF = 0x3010;
                PORTE = 0x0200;
                PORTA = 0x0032;
                for (i = 0; i < 1000; i++);

                if (PORTAbits.RA5 == 0) {
                    DRV_USART0_WriteByte('3');
                    c2[dig] = 3;

                    dig++;

                } else if (PORTAbits.RA4 == 0) {
                    DRV_USART0_WriteByte('6');
                    c2[dig] = 6;

                    dig++;

                } else if (PORTAbits.RA1 == 0) {
                    DRV_USART0_WriteByte('9');
                    c2[dig] = 9;

                    dig++;

                } else if (PORTEbits.RE9 == 0) {
                    DRV_USART0_WriteByte('e');
                }

                PORTF = 0x2030;
                PORTE = 0x0200;
                PORTA = 0x0032;
                for (i = 0; i < 1000; i++);

                if (PORTAbits.RA4 == 0) {
                    DRV_USART0_WriteByte('b');
                } else if (PORTAbits.RA5 == 0) {
                    DRV_USART0_WriteByte('a');
                } else if (PORTAbits.RA1 == 0) {
                    DRV_USART0_WriteByte('c');
                } else if (PORTEbits.RE9 == 0) {
                    DRV_USART0_WriteByte('d');
                }

                for (i = 0; i < 1000; i++);
            } // end if dig <3
            if (dig == 3) {
                attempts++;
                DRV_USART0_WriteByte('-');

                appData.state = nextattempt;
            }
            break;

        }


        case nextattempt:
        {
            if (attempts == 0) {
                PORTG = 0x1000;
                int i = 0;
                for (; i < 1000000; i++);
            } else if (attempts == 1) {
                PORTG = 0x3000;
                int i = 0;
                for (; i < 1000000; i++);
            } else if (attempts == 2) {
                PORTG = 0x7000;
                int i = 0;
                for (; i < 1000000; i++);
            }
            appData.state = check;

            break;

        }



        case RX:
        {
            static int rx_index = 0;
            if (!DRV_USART0_ReceiverBufferIsEmpty()) {
                temp = DRV_USART0_ReadByte();
                if (temp >= '0' && temp <= '9') {
                    c[rx_index++] = temp - '0';
                    //                    DRV_USART0_WriteByte(temp); // to check if it's right can be deleted
                }
            }

            if (rx_index == 3) {
                //                rx_index = 0;
                dig = 0;
                attempts = 0;
                appData.state = enter;

            }
            break;
        }


        case TX:
        {
            //                                    appData.flageled = 0;

            if (success == 1) {
                LATG = 0xF000;
                int j;
                char M[20] = " succeess ";
                for (j = 0; M[j]; j++)
                    DRV_USART0_WriteByte(M[j]);

                appData.state = FS;
                //                          appData.flageled = 0;

                break;

            } else if (success == 0) {
                LATG = 0x0000;
                int j;
                char M[20] = " fails ";
                for (j = 0; M[j]; j++)
                    DRV_USART0_WriteByte(M[j]);
                appData.flageled = 1;
                success = 5;
                //                DRV_USART0_WriteByte('d');

                break;

                //                                      appData.state = RX; // change it to fails case of flashing leds
            }

            //    int k;
            //    for(k=0;k<20;k++)
            //        c[k]='\0';


            break;
        }


        case check:
        {
            //                                    appData.flageled = 0;
            //                                    DRV_TMR0_Close();

            equal = true;
            int j = 0;
            for (; j < 3; j++) {
                if (c[j] != c2[j]) {
                    equal = false;
                    break;
                }
            }

            if (equal) {
                success = 1;
                appData.state = TX;
            } else {
                if (attempts >= 3) { // is  2 right to have 3 attempts ?!
                    success = 0;
                    appData.state = TX;
                } else {
                    appData.state = enter;
                    dig = 0; // Reset digit count for next attempt


                }
            }
            break;
        }



        case FS: //full step stepper motore
        {

            int number = c[0] * 100 + c[1] * 10 + c[2];


            result = ceil((number / 1.8) / 4); //example: 90 degree --> 50 step ... 50/4=12.5
            int i = 0;
            int j = 0;
            int k = 0;
            for (j = 0; j < result; j++) {

                for (k = 0; k < 4; k++) {

                    PORTB = FSarray[k] << 7; // to read from RB7 -

                    for (i = 0; i < 500000; i++) { // half of FS speed with same delay 
                    }

                }

            }
            //                                        DRV_USART0_WriteByte('b');

            appData.state = noop;
            break;
        }

        case flashing:
        {
            LATG = PORTG ^ 0x0F000;
            appData.state = noop;

            break;
        }



        case noop:
        {


            break;
        }

            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}



/*******************************************************************************
 End of File
 */
