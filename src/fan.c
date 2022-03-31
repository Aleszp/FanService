/**************************************************
 * FanService - PWM controlled fan driver for Rapsberry Pi
 * version: alpha-1.5
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
	AGPLnotice();
	int status=gpioInitialise();
	if(status<0)
	{
	   	fprintf(stderr,"GPIO initialisation failed, error code: %i.\n",status);
	   	return status;
	}

	signal(SIGTERM, terminate);
	signal(SIGINT, terminate);

	uint32_t stop=0,min=64,max=255,Tstart=45,Tstop=40,Tmax=70,pinID=18;
	uint32_t T=0;
	uint32_t dutyCycle=0;
	loadConfig(&stop,&min,&max,&Tstart,&Tstop,&Tmax,&pinID);
	gpioSetMode(pinID, PI_OUTPUT);
	fprintf(stdout,"Freq=%i\n",gpioGetPWMfrequency(pinID));
	gpioHardwarePWM(pinID,40000,0);
	fprintf(stdout,"Freq=%i\n",gpioGetPWMfrequency(pinID));
	fprintf(stdout,"Range=%i\n",gpioGetPWMrealRange(pinID));
	gpioSetPWMrange(pinID,6250);
	fprintf(stdout,"Range=%i\n",gpioGetPWMrealRange(pinID));
	gpioSetPullUpDown(18, PI_PUD_DOWN);

	while(1)
	{
		T=getTemperature()/1000;
		dutyCycle=calculateDutyCyle(&T,&stop,&min,&max,&Tstart,&Tstop,&Tmax);
		dutyCycle=2125;
		gpioPWM(pinID,dutyCycle);
		fprintf(stdout,"SetdutyCycle=%u\n",gpioGetPWMdutycycle(pinID));
		fprintf(stdout,"T=%u, dutyCcycle=%u\n",T,dutyCycle);
		sleep(1);
	}

	return 0;
}
