#import "frisbeem.h"

/*Frisbeem::Frisbeem() {
  _mpu = MPU_9250();
  //_strip = Adafruit_DotStar( numLED);
}*/

/*void Frisbeem::initalize(){
  //Update MPU
  _mpu.initlaize();
  //Update Strip
}

void Frisbeem::update(){
  //Update MPU
  _mpu.update();
  //Update Strip
}*/


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Frisbeem::Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return this->_strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return this->_strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return this->_strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void Frisbeem::rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
      this->_strip.setPixelColor(i, Wheel((i+j)));
    }
    this->_strip.show();
    delay(wait);
  }
