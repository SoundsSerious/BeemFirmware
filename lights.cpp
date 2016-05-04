#import "lights.h"


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Lights::wheel(byte WheelPos) {
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

void Lights::blue() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(255));
  }
  _strip.show();
}

void Lights::green() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(60));
  }
  _strip.show();
}

void Lights::red() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(180));
  }
  _strip.show();
}
void Lights::off() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, _strip.Color(0,0,0));
  }
  _strip.show();
}

void Lights::rainbow(uint8_t wait) {
  uint16_t i;
  if (whl > 255){
    whl = 0;
  }
  for(i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, wheel((i+whl)));
  }
  whl++;
  _strip.show();
  delay(wait);

}

// Set all pixels in the strip to a solid color, then wait (ms)
void Lights::colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
  }
  _strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color, wait (ms) after each one
void Lights::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
    _strip.show();
    delay(wait);
  }
}
