#include "application.h"
//#include "globals.h"
#include "frisbeem.h"
#include "i2c_hal.h"

//using namespace std;
//WARNING: I SUCK AT SPELLING. FEEL FREE TO FIX ANY SPELLING ERRORS XP

//SYSTEM_MODE(MANUAL); //Switch to manual when away from network

Frisbeem frisbeem = Frisbeem();

#define I2C_SPEED (uint32_t)400000 //400Khz can push 600Khz sometimes


void setup() {

Wire.setSpeed(I2C_SPEED);

frisbeem.initlaize();
frisbeem._lights._strip.brightness = brightness;

}

void loop() {

frisbeem.update();

}
