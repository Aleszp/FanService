/**************************************************
 * FanService - PWM controlled fan driver for Rapsberry Pi
 * version: alpha-1.1
 * (c) Aleksander Szpakiewicz-Szatan, 2022
 **************************************************/
//Use libpigpio to control PWM pins
#include <pigpio.h>

//Use stdio access temperature data and communicate with user
#include <stdio.h>
#include <stdint.h>

//Use signal to properly deinitialize gpio on termination
#include <signal.h>

#include "functions.h"


int main(void)
{
	int status=gpioInitialise()
	if(status<0)
	{
	   	fprintf(stderr,"GPIO initialisation failed, error code: %i.\n",status);
	   	return status;
	}
	
	signal (SIGTERM, terminate);
	
	while(1)
	{
		
	}
	
	return 0;
}
