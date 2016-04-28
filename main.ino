#import "application.h"
#import "frisbeem.h"
#import "dotstar.h"
#include "i2c_hal.h"

Frisbeem frisbeem = Frisbeem();

#define I2C_SPEED (uint32_t)400000 //400Khz can push 600Khz sometimes
int numLED;
uint8_t whl;
uint8_t *pixels;

void setup() {
Wire.setSpeed(I2C_SPEED);
Serial.begin(115200);
frisbeem.initalize();
Serial.println("Hello...Starting");

numLED = frisbeem._strip.numPixels();
Serial.print("We have ");Serial.print(numLED);Serial.println(" LEDs");

}

void loop() {

frisbeem.update();

}

void pixelDebugPrint(){

  numLED = frisbeem._strip.numPixels();
  Serial.print("We have ");Serial.print(numLED);Serial.println(" LEDs");
  for (int k=0; k<numLED; k++)
  {
    Serial.print( frisbeem._strip.getPixelColor(k));
    Serial.print("|");
  }
  Serial.println("|\r\n\r\n");

}
