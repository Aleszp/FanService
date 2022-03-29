//Use libpigpio to control PWM pins
#include <pigpio.h>

//Use stdio for access to temperature
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#include "functions.h"

//Deinitialise gpio on termination
void terminate(int signal)
{
	fprintf(stdout,"Terminating GPIO.\n");
	gpioTerminate();
	exit(signal);
}

//Loads config parameters, otherwise returns default data, stub for future external config support
void loadConfig(uint8_t* stop, uint8_t* min, uint8_t* max, uint8_t* Tstart, uint8_t* Tstop, uint8_t* Tmax, uint8_t* pinID)
{
	//0% duty cycle when stopped
	*stop=0;
	//minimal duty cycle 25%
	*min=64;
	//maximal duty cycle 100%
	*max=255;
	//Start fan above 45*C
	*Tstart=45;
	//Stop fan below 40*C
	*Tstop=40;
	//Set full dutycycle above 70*C
	*Tmax=70;
	//Set output pin to 18
	*pinID=18;
}

uint8_t getTemperature()
{
	FILE* temp=fopen("/sys/class/thermal/thermal_zone0/temp","r");
	if(!temp)
	{
		fprintf(stderr,"Could not open /sys/class/thermal/thermal_zone0/temp to read.\n");
		terminate(SIGABRT);
	}
		
	uint32_t T;
	fscanf(temp,"%i",&T);
	fclose();
	return(uint8_t) T/1000;
}

uint8_t calculateDutyCyle(uint8_t T, uint8_t stop, uint8_t min, uint8_t max, uint8_t Tstart, uint8_t Tstop, uint8_t Tmax)
{
	if(T<Tstop)
		return stop;
	if(T<=Tstart)
		return min;
	if(T>Tmax)
		return max;
	
	uint16_t tmp=((Tmax-T)*(max-min));
	tmp/=(Tmax-Tmin);
	tmp+=min;
	if(tmp>max)
		tmp=max;
	return (uint8_t)tmp;
}
