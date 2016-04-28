#import "frisbeem.h"

/*Frisbeem::Frisbeem() {
  _mpu = &MPU_9250();
  strip = &Adafruit_DotStar(54);
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
   return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void Frisbeem::blue() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, Wheel(255));
  }
  _strip.show();
}

void Frisbeem::rainbow(uint8_t wait) {
  uint16_t i;
  if (whl > 255){
    whl = 0;
  }
  for(i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, Wheel((i+whl)));
  }
  whl++;
  _strip.show();
  delay(wait);

}

// Set all pixels in the strip to a solid color, then wait (ms)
void Frisbeem::colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
  }
  _strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color, wait (ms) after each one
void Frisbeem::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
    _strip.show();
    delay(wait);
  }
}
