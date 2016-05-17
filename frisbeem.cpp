#include "frisbeem.h"

void Frisbeem::initlaize(){
  //Initalize communication
  _com.initialize();
  _com.log("Communication Started...");
  _com.log("Go For Initlaize");
  //Update MPU
  _com.log("Go For Brains");
  _mpu.initialize();
  //Update Strip
  _com.log("Go For Lights");
  _lights.initlaize();
  //Serial.println("Swith State Creation");
  _com.log("Initalizing Motion...");
  _motionState = StateSwitch();
  //Serial.println("Motion State Creation");
  _com.log("Go For Motion");
  _motionState.initialize();
  _com.log("Go For Loop");
}

void Frisbeem::update(){
  //Open COM to end client if conditions are correct
  _com.open();
  //Tick The Log So It Can Output Periodically
  _com.tick();

  _com.log("Beeming Into Space...");
  //Update COM layer
  _com.update();


  //Handle Other Stuff
  _com.log("Updating...");
  //Update MPU
  _com.log("Updating MPU");
  _mpu.update();

  //create newEvent and process events (circular buffer)
  _com.log("Generating Events");
  processEvents();
  //Notify Observers Of new Event
  _com.log("Hollerin'");
  notify( newEvent );
  //Send Event To Current Motion State
  //Serial.println("Calling handleInput");
  _com.log("Making Decisions");
  _motionState.handleInput( newEvent );
  //Initialize Lights
  _com.log("Puttin On The High Beems!");
  updateThetaOffset();
  _lights.update(1);

  //Close COM to end client
  _com.close();
}

void Frisbeem::updateThetaOffset()
{
  thisTime = micros();

  //Integrate For Theta
  thetaOffset -= _mpu.G.z * (thisTime - lastTime) / 1000000;
  //Catch & Adjust For Theta Over Limit
  if (thetaOffset > 360){
    thetaOffset -= 360;
  }
  else if (thetaOffset < 0){
    thetaOffset += 360;
  }

  lightOffset = thetaOffset / degPerPixel;

  //Preserve Time Calculations
  lastTime = thisTime;
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
  return Event( _mpu.G.z );
}


Event *Frisbeem::getCurrentEvent()
{
  return _events[ _currentEventIndex ];
}

void Frisbeem::setCurrentEvent(Event *event)
{
  _events[ _currentEventIndex ] = event;
}
