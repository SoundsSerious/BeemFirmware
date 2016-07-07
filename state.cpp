#import "state.h"
#import "globals.h"

//Make One Internal Instance Of MotionData to Share
MotionData motionData = MotionData();

void StateSwitch::handleInput( Event &event)
{ frisbeem._com.log("Switch Handiling Input: "+event.type());
  State *s = stateNow();
  event.visit( s );
}

////////////////////////////////////////////////////////////////////////////////
//MOTION STATES
////////////////////////////////////////////////////////////////////////////////

void MotionSwitch::initialize()
{
  //Add States In Order Of ENUM (Because It Matters!)
  _states.push_back(&restState);
  _states.push_back(&motionState);
  _states.push_back(&spinState);
}

void MotionSwitch::handleInput( Event &event)
{ frisbeem._com.log("MotionSwitch Handiling Input: "+event.type());
  MotionState *s = stateNow();
  event.visit( s );
}

void MotionSwitch::handleInput( MotionEvent &motion)
{ frisbeem._com.log("MotionSwitch Handiling Motion Input: "+motion.type());
  MotionState *s = stateNow();
  motion.visit( s );
}

MotionState::MotionState()
{
  _motionData = &motionData;
}

void MotionState::handleInput( MotionEvent &motion )
{
  _motionEvent = &motion;
  //Check Spin
  if ( motion.G.z > ( _motionData -> spinThreshold) )
  {
    frisbeem._motionState.currentState = MotionSwitch::SPIN;
  }
  else if( frisbeem._mpu.rest ) //Check If Resting
  {
    frisbeem._motionState.currentState = MotionSwitch::REST;
  }
  else{ frisbeem._motionState.currentState = MotionSwitch::MOTION; }

  //Update State
  update();
  //Set Values Going Out
  Glast = motion.G;
  Alast = motion.A;
  Vlast = motion.V;
  Xlast = motion.X;
}

void MotionState::update()
  { //Initialize and do some physics math
      frisbeem._com.log("MotionState Updating..");
      _motionData -> now = micros();
      _motionData -> newOmega = _motionEvent -> G.z;//();
      _motionData -> dOmega = _motionData -> newOmega - _motionData -> lastOmega;
      _motionData ->dt = (_motionData ->now - _motionData ->lastTime);
      _motionData ->dOmegaDt = _motionData ->dOmega *1E6/ _motionData ->dt;



      //Apply Torque Through Low Pass Filter
      _motionData ->_torque = 0.008748 * _motionData ->dOmegaDt;
      _motionData ->torque = 0.95 * _motionData ->_torque + 0.05 * _motionData ->torque;

      //Serial.print("Torque \t");Serial.println(torque);
      //Serial.print("Omega \t");Serial.println(newOmega);
      if (_motionData ->newOmega > 200){ //Airborne
          _motionData ->stationaryCount = 0;
          _motionData ->moving = true;
          //Serial.println("Moving...");
          _motionData ->sleepModeActivated = false;
      }
      else{
        //Serial.println("Stationary...");
        _motionData ->stationaryCount++;
        _motionData ->moving = false;
        if (_motionData ->stationaryCount > _motionData ->sleepThreshold){
          //Serial.println("Greater Than threshold");
         if (_motionData ->stationaryCount > _motionData ->stationaryReset){
           _motionData ->stationaryCount = 0;
         }
         _motionData ->stationaryCount = _motionData ->stationaryCount + 10;
         _motionData ->sleepModeActivated = true;
        }
        else{
          //Serial.print("stationaryCount");Serial.println( stationaryCount);
          _motionData ->sleepModeActivated = false;

        }
      }
      if (_motionData ->sleepModeActivated){
       //Turn Off Lights. Switch Arduino to Low Power Consumption.
       frisbeem._com.log("Sleep Mode");
      }
      else {
        if (_motionData ->moving) { //Rainbow Pattern
          frisbeem._com.log("Airborne");
        }
        else{ //Stationary
          frisbeem._com.log("Stationary");
        }
      }
      //delay(50);//temp
      //Setup For Next Update
      _motionData ->lastTime = _motionData ->now;
      _motionData ->lastOmega = _motionData ->newOmega;
  }
