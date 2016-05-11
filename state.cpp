#import "state.h"
#import "globals.h"

void StateSwitch::initialize(){
  frisbeem._com.log("Pointer Assignment");

  _states.push_back( new MotionState() );
  frisbeem._com.log(String("Last Item") + String(_states.back() -> msg ));
}

int MotionState::handleInput(Event &event)
  { //Initialize and do some physics math
    now = micros();
    newOmega = event.abs_omega;
    dOmega = newOmega - lastOmega;
    dt = (now - lastTime);
    dOmegaDt = dOmega *1E6/ dt;



    //Apply Torque Through Low Pass Filter
    _torque = 0.008748 * dOmegaDt;
    torque = 0.95 * _torque + 0.05 * torque;

    //Serial.print("Torque \t");Serial.println(torque);
    //Serial.print("Omega \t");Serial.println(newOmega);
    if (newOmega > 200){ //Airborne
        stationaryCount = 0;
        moving = true;
        //Serial.println("Moving...");
        sleepModeActivated = false;
    }
    else{
      //Serial.println("Stationary...");
      stationaryCount++;
      moving = false;
      if (stationaryCount > sleepThreshold){
        //Serial.println("Greater Than threshold");
       if (stationaryCount > stationaryReset){
         stationaryCount = 0;
       }
       stationaryCount = stationaryCount + 10;
       sleepModeActivated = true;
      }
      else{
        //Serial.print("stationaryCount");Serial.println( stationaryCount);
        sleepModeActivated = false;

      }
    }
    if (sleepModeActivated){
     //Turn Off Lights. Switch Arduino to Low Power Consumption.
     frisbeem._com.log("Sleep Mode");

    }
    else {
      if (moving) { //Rainbow Pattern
        frisbeem._com.log("Airborne");
        currentState = AIRBORNE;
      }
      else{ //Stationary
        frisbeem._com.log("Stationary");
        currentState = STATIONARY;
      }
    }
    //delay(50);//temp
    //Setup For Next Update
    lastTime = now;
    lastOmega = newOmega;
  }
