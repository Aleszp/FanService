//Use libpigpio to control PWM pins
#include <pigpio.h>

//Use stdio for access to temperature
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#include "functions.h"


void AGPLnotice()
{
	fprintf(stdout,"FanService, service for controlling RaspberryPi fan with PWM\n");
	fprintf(stdout,"Copyright (C) 2022  Aleksander Szpakiewicz-Szatan\n\n");
	fprintf(stdout,"This program is free software: you can redistribute it and/or modify\n");
	fprintf(stdout,"it under the terms of the GNU Affero General Public License as published\n");
	fprintf(stdout,"the Free Software Foundation, either version 3 of the License, or\n");
	fprintf(stdout,"(at your option) any later version.\n\n");

	fprintf(stdout,"This program is distributed in the hope that it will be useful,\n");
	fprintf(stdout,"but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	fprintf(stdout,"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	fprintf(stdout,"GNU General Public License for more details.\n\n");

	fprintf(stdout,"You should have received a copy of the GNU Affero General Public License\n");
	fprintf(stdout,"along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n");

	fprintf(stdout,"Source available: <https://github.com/Aleszp/FanService>.\n");
	fprintf(stdout,"Contact: aleksander.szsz(a)gmail.com\n\n");
}

//Deinitialise gpio on termination
void terminate(int signal)
{
	fprintf(stdout,"Terminating GPIO.\n");
	gpioTerminate();
	exit(signal);
}

//Loads config parameters, otherwise returns default data, stub for future external config support
void loadConfig(uint32_t* stop, uint32_t* min, uint32_t* max, uint32_t* Tstart, uint32_t* Tstop, uint32_t* Tmax, uint32_t* pinID)
{
	//0% duty cycle when stopped
	*stop=0;
	//minimal duty cycle 25%
	*min= 2500;
	//maximal duty cycle 100%
	*max=10000;
	//Start fan above 45*C
	*Tstart=45;
	//Stop fan below 40*C
	*Tstop=40;
	//Set full dutycycle above 70*C
	*Tmax=70;
	//Set output pin to 18
	*pinID=18;
}

uint32_t getTemperature()
{
	FILE* temp=fopen("/sys/class/thermal/thermal_zone0/temp","r");
	if(!temp)
	{
		fprintf(stderr,"Could not open /sys/class/thermal/thermal_zone0/temp to read.\n");
		terminate(SIGABRT);
	}

	uint32_t T;
	fscanf(temp,"%u",&T);
	fclose(temp);
	return T;
}

uint32_t calculateDutyCyle(uint32_t* T, uint32_t* stop, uint32_t* min, uint32_t* max, uint32_t* Tstart, uint32_t* Tstop, uint32_t* Tmax)
{
	if(*T<*Tstop)
		return *stop;
	if(*T<=*Tstart)
		return *min;
	if(*T>*Tmax)
		return *max;

	uint32_t tmp=((*Tmax-*T)*(*max-*min));
	tmp/=(*Tmax-*Tstart);
	tmp+=*min;
	if(tmp>*max)
		tmp=*max;
	return tmp;
}
