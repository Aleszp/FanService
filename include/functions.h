#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

void AGPLnotice();
void terminate(int signal);
void loadConfig(uint32_t* stop, uint32_t* min, uint32_t* max, uint32_t* Tstart, uint32_t* Tstop, uint32_t* Tmax, uint32_t* pinID);
uint32_t getTemperature();
uint32_t calculateDutyCyle(uint32_t *T, uint32_t *stop, uint32_t *min, uint32_t *max, uint32_t *Tstart, uint32_t *Tstop, uint32_t *Tmax);

#endif
