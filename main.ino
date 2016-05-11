#include "application.h"
#include "globals.h"
#include "frisbeem.h"
#include "i2c_hal.h"

//using namespace std;
//WARNING: I SUCK AT SPELLING. FEEL FREE TO FIX ANY SPELLING ERRORS XP

//SYSTEM_MODE(MANUAL); //Switch to manual when away from network
//SYSTEM_MODE( SEMI_AUTOMATIC ); //Switch to manual when away from network
Frisbeem frisbeem;

#define I2C_SPEED (uint32_t)400000 //400Khz can push 600Khz sometimes


void setup() {

Wire.setSpeed(I2C_SPEED);

//Particle.connect();
frisbeem.initlaize();
frisbeem._com.log("Finish Setup");

}

void loop() {

frisbeem.update();
//Particle.process();
/*if (Particle.connected() == false) {
  log("Connecting To Cloud");

}*/

  /*if (WiFi.ready()){

  }*/
}
