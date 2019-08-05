# TivaC-Series-interrupt
In its simplest form, this lab is designed to blink several LEDs on the Tiva Series Launchpad and Digilent Orbit Board using an interrupt. It will help familiarize the individuals with concepts involving interrupts and APIs (Application Program Interface) which are routines, protocols, and tools for building software applications.

After including the proper header files, the port and I/O pin that’s utilized for the interrupt needs to be enabled. Switch 2 on the Tiva LaunchPad was implemented as the interrupt for this lab, so PORT A and pin 6 are added into the setup for initialization. After the correct pin is set up, a macro definition for the interrupt has to be created as a global variable. 

In this lab, there are two macro definitions that need to be added: #define Lab5_Solution and #define Lab5_Problem. Later in the code, directives are used to control the conditional compilation of the program. The #define Lab5_Solution directive enables PORT A pin 6 on the rising edge of Switch 2. The #define Lab5_Problem directive listens for the rising edge of Switch 2 which begins a function that contains a while loop that blinks four LEDs on the obrite board, as well as the RGB LED on the LaunchPad while changing its color to white. 

Next, a startup file that contains a vector table that defines what code handles the interrupt needs to be altered. The startup file is a .c file called “tm4c123gh6pm_startup_ccs.c” which contains “an array of pointers to memory locations for an array of functions which neither receive nor return any parameters. Those functions are the various exception and interrupt handlers” [1]. Within the array, the Interrupt function that was created, void GPIO_PORTA_isr(void), is called on the line that relates to the address of GPIO PORT A on the Tiva Series Launchpad. Lastly, this function also needs to be declared at the top using extern void GPIO_PORTA_isr(void) which will extend the visibility of this function. 


References

[1] https://learningmicros.files.wordpress.com/2017/04/exceptions-interrupts-and-startup.pdf
