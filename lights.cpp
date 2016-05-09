#import "lights.h"
#import "globals.h"

void Lights::initlaize()
{
  _strip.begin();
  //Loading Effect :)
  off();
  _strip.show();
  colorWipe( wheel( 255 ), 20);
  _strip.show();
  delay(100);
}

void Lights::update()
{
  if (frisbeem._motionState.stateNow() -> sleepModeActivated){
    off();
    delay(250);
  }
  else{
    rainbow( 2, frisbeem.lightOffset );
  }
  off();
}

void Lights::onNotify( Event &event)
{
};

// Cool and useful color functions
void Lights::rainbow(uint8_t wait,uint8_t offset) {
  uint16_t i;
  int current;
  int numPixels = _strip.numPixels();
  if (whl > 255){
    whl = 0;
  }
  for(i=0; i< numPixels; i++) {
      current = i - offset;
      if (current < 0){ //Normal Assignment
        current = numPixels + current;
      }
    _strip.setPixelColor(current, wheel((i+whl)));
    if ( i == 0 ){
      _strip.setPixelColor(current, _strip.Color(255,0,0));
    }
  }
  whl++;
  _strip.show();
  delay(wait);

}

void Lights::quarters(uint32_t c,uint32_t c2, uint8_t offset)
{ //Split Lights by 4 and color a quarter
  uint16_t i;
  int numPixels = _strip.numPixels();
  int quarterNumber = numPixels / 4;
  int remdr = numPixels % 4;
  int current;

  for (i=0; i<numPixels; i++){
    current = i - offset;
    if (current < 0){ //Normal Assignment
      current = numPixels + current;
    }
    if ( i < numPixels / 4){
      _strip.setPixelColor(current, c);
    }
    else if ( i < numPixels * 1 / 2){
      _strip.setPixelColor(current, _strip.Color(0,0,0));
    }
    else if ( (i-1) < numPixels * 3 / 4){
      _strip.setPixelColor(current, c2);
    }
    else{
      _strip.setPixelColor(current, _strip.Color(0,0,0));
    }
  }
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
