#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

void terminate(int signal);
void loadConfig(uint8_t* stop, uint8_t* min, uint8_t* max, uint8_t* Tstart, uint8_t* Tstop, uint8_t* Tmax)
uint8_t calculateDutyCyle(uint8_t T, uint8_t stop, uint8_t min, uint8_t max, uint8_t Tstart, uint8_t Tstop, uint8_t Tmax);

#endif
