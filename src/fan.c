/**************************************************
 * FanService - PWM controlled fan driver for Rapsberry Pi
 * version: alpha-1.4
 * (c) Aleksander Szpakiewicz-Szatan, 2022
 **************************************************/
//Use libpigpio to control PWM pins
#include <pigpio.h>

//Use stdio access temperature data and communicate with user
#include <stdio.h>
#include <stdint.h>

//Use signal to properly deinitialize gpio on termination
#include <signal.h>
//Use unistd to sleep
#include <unistd.h>

#include "functions.h"


int main(void)
{
	int status=gpioInitialise();
	if(status<0)
	{
	   	fprintf(stderr,"GPIO initialisation failed, error code: %i.\n",status);
	   	return status;
	}
	
	signal(SIGTERM, terminate);
	signal(SIGINT, terminate);
	
	uint8_t stop=0,min=64,max=255,Tstart=45,Tstop=40,Tmax=70,pinID=18;
	uint8_t T=0;
	uint8_t dutyCycle=0;
	loadConfig(&stop,&min,&max,&Tstart,&Tstop,&Tmax,&pinID);
	gpioSetMode(pinID, PI_OUTPUT);
	gpioSetPWMrange(pinID,max);
	gpioHardwarePWM(pinID,100000,0);
	while(1)
	{
		T=getTemperature();
		dutyCycle=calculateDutyCyle(T,stop,min,max,Tstart,Tstop,Tmax);
		gpioPWM(pinID,dutyCycle);
		sleep(1);
	}
	
	return 0;
}
