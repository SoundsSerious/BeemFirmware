#include "frisbeem.h"

void Frisbeem::initlaize(){
  //Initalize communication
  _com.initialize();
  _com.log("Communication Started...");
  _com.log("Go For Initlaize");
  //Update MPU
  _mpu.initlaize();

  //Update Strip
  _lights._strip.begin();
  _lights._strip.show();
  //Serial.println("Swith State Creation");
  _motionState = StateSwitch();
  //Serial.println("Motion State Creation");
  _motionState.initialize();
  _com.log("Go For Loop");
}

void Frisbeem::update(){
  _com.log("Updating...");
  //Update MPU
  _mpu.update();
  //Update COM layer
  _com.update();
  //create newEvent and process events (circular buffer)
  processEvents();
  //Notify Observers Of new Event
  notify( newEvent);
  //Send Event To Current Motion State
  //Serial.println("Calling handleInput");
  _motionState.handleInput( newEvent );
}

void Frisbeem::processEvents()
{ //Generate A New Event & Add to circular buffer after deleting current item
  //Serial.print("Getting New Event #");Serial.println(_eventCount);
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
