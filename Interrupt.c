******************************************************
Chip type               : ARM TM4C123GH6PM
Program type            : Firmware
Core Clock frequency    : 80.000000 MHz
*******************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

// Macro definitions
#define Lab5_Problem
#define Lab5_Solution
// --------------------------------------

void main(void) {
    
    // Setting the internal clock
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // Enable Peripheral ports for input/ output
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  //PORTC
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7); // LED 1 LED 2

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);              //PORTB
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);     // LED 4

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);              //PORT D
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);     // LED 3
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);     // BTN 1

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);              //PORT F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
// RGB LED on Launchpad

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);              //PORT A
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);     // Switch 2


//------------------------------------------
#ifdef Lab5_Solution
    IntEnable(INT_GPIOA_TM4C123);      //sets the interrupt controller to interrupt on GPIO port A
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_6);                             //Orbit SW2
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_RISING_EDGE);      //RISING edge
    IntMasterEnable();                                                              //turns on all interrupts
#endif
//-------------------------------------------
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4); 
// LED Blue on Launchpad
    // Cycle through the LEDs on the Orbit board
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x40); // LED 1 & 2 Off
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);         // LED 3 off
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);         // LED 4 off
        SysCtlDelay(6000000);             // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x80); // LED 1&2 on
        SysCtlDelay(6000000);             // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00); //LED 1&2 off
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x40);         // LED 3 on
        SysCtlDelay(6000000);             // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);         // LED 3 off
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);         // LED 4 on
        SysCtlDelay(6000000);             // Delay, Replaces for LOOP
        
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8); 
//  LED Green on Launchpad

// Cycle through the LEDs on the Orbit board
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00); // LED 1&2 Off
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);         // LED 3 off
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20); // LED 4 on
        SysCtlDelay(6000000); // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00); // LED 4 off
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x40); // LED 3 on
        SysCtlDelay(6000000); // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x80); // LED 1&2 on
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00); // LED 3 off
        SysCtlDelay(6000000); // Delay, Replaces for LOOP

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x40); // LED 1&2 Off
        SysCtlDelay(6000000); // Delay, Replaces for LOOP

#ifdef Lab5_Problem
    while(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6)){             // Listen for SW2
                                    // All LED Blink
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0xFF);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0xFF);
 // White Output
        SysCtlDelay(2000000);                    //Delay

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00); // LEDs off
        SysCtlDelay(2000000);                    //Delay
    }
#endif
        }
}
void GPIO_PORTA_isr(void){
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_6);         // Clear Interrupts
    while(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6)){      // Listen for SW2
        // All LED Blink
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0xFF);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0xFF);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0xFF);
// White Output
        SysCtlDelay(2000000);                //Delay

        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7, 0x00);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0x00);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00); //LEDs off

        SysCtlDelay(2000000);                //Delay
    }
}
