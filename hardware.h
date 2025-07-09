#ifndef HARDWARE_H
#define HARDWARE_H

void setupHardware();
void setLED(bool state);
void setBuzzer(bool state, int frequency = 2000);
bool getPIRState();
void stopAllOutputs();

#endif
