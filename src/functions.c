//Use libpigpio to control PWM pins
#include <pigpio.h>

//Use stdio for access to temperature
#include <stdio.h>
#include <stdint.h>

#include "functions.h"

//Deinitialise gpio on termination
void terminate(int signal)
{
	fprintf(stdout,"Terminating GPIO.\n");
	gpioTerminate();
}
