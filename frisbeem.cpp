#import "frisbeem.h"

void Frisbeem::initlaize(){
  //Update MPU
  _mpu.initlaize();
  //Update Strip
  _strip.begin();
  _strip.show();
  Serial.println("Swith State Creation");
  _motionState = StateSwitch();
  Serial.println("Motion State Creation");
  _motionState.initialize();
  //_ms = MotionState();
  //_motionState._states[0] = &_ms;
}

void Frisbeem::update(){
  //Update MPU
  _mpu.update();
  //Update Strip
  rainbow(25);
  //create newEvent and process events (circular buffer)
  processEvents();
  //Notify Observers Of new Event
  notify( *this, newEvent);
  //Send Event To Current Motion State
  Serial.println("Calling handleInput");
  _motionState.handleInput( newEvent );
}

void Frisbeem::processEvents()
{ //Generate A New Event & Add to circular buffer after deleting current item
  Serial.print("Getting New Event #");Serial.println(_eventCount);
  newEvent = genNextEvent();
  _eventCount++;
  //Delete Current Item & Add To Buffer
  // delete getCurrentEvent();
  // setCurrentEvent( &newEvent);
  // Serial.println("Added New Event To Queue");
  // //Move Tail Index And
  // _currentEventIndex++;
  // if (_currentEventIndex >= NUM_EVENTS - 1)
  // { Serial.println("Resetting Queue Index");
  //   _currentEventIndex = 0;
  // }

}

Event Frisbeem::genNextEvent()
{ //For Now Look At Omegea (w)
  return Event( _mpu.gz );
}


Event *Frisbeem::getCurrentEvent()
{
  return _events[ _currentEventIndex ];
}

void Frisbeem::setCurrentEvent(Event *event)
{
  _events[ _currentEventIndex ] = event;
}

// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t Frisbeem::wheel(byte WheelPos) {
//   if(WheelPos < 85) {
//    return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//   } else if(WheelPos < 170) {
//    WheelPos -= 85;
//    return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   } else {
//    WheelPos -= 170;
//    return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
// }
//
// void Frisbeem::blue() {
//   uint16_t i, j;
//
//   for(i=0; i<_strip.numPixels(); i++) {
//       _strip.setPixelColor(i, wheel(255));
//   }
//   _strip.show();
// }
//
// void Frisbeem::rainbow(uint8_t wait) {
//   uint16_t i;
//   if (whl > 255){
//     whl = 0;
//   }
//   for(i=0; i<_strip.numPixels(); i++) {
//     _strip.setPixelColor(i, wheel((i+whl)));
//   }
//   whl++;
//   _strip.show();
//   delay(wait);
//
// }
//
// // Set all pixels in the strip to a solid color, then wait (ms)
// void Frisbeem::colorAll(uint32_t c, uint8_t wait) {
//   uint16_t i;
//
//   for(i=0; i<_strip.numPixels(); i++) {
//     _strip.setPixelColor(i, c);
//   }
//   _strip.show();
//   delay(wait);
// }
//
// // Fill the dots one after the other with a color, wait (ms) after each one
// void Frisbeem::colorWipe(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<_strip.numPixels(); i++) {
//     _strip.setPixelColor(i, c);
//     _strip.show();
//     delay(wait);
//   }
// }
