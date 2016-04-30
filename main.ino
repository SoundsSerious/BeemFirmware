#import "application.h"
#import "frisbeem.h"
#import "dotstar.h"
#include "i2c_hal.h"

//using namespace std;
//WARNING: I SUCK AT SPELLING. FEEL FREE TO FIX ANY SPELLING ERRORS XP

extern Frisbeem frisbeem = Frisbeem();

#define I2C_SPEED (uint32_t)400000 //400Khz can push 600Khz sometimes
uint8_t brightness = 50;

void setup() {
Wire.setSpeed(I2C_SPEED);
Serial.begin( 115200 );
Serial.println("Initlaize");
frisbeem.initlaize();

frisbeem._strip.brightness = brightness;

}

void loop() {

Serial.println("Updating");
frisbeem.update();

}

/*void pixelDebugPrint(){

  int numLED = frisbeem.frisbeem._strip.numPixels();
  Serial.print("We have ");Serial.print(numLED);Serial.println(" LEDs");
  for (int k=0; k<numLED; k++)
  {
    Serial.print( frisbeem.frisbeem._strip.getPixelColor(k));
    Serial.print("|");
  }
  Serial.println("|\r\n\r\n");

}*/
