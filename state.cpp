#import "state.h"

void StateSwitch::initialize(){
  Serial.println("Pointer Assignment");

  _states.push_back( new MotionState() );
  Serial.print("Last Item"); Serial.println( _states.back() -> msg );
}

int MotionState::handleInput(Entity &entity, Event &event)
  { //Initialize and do some physics math
    now = micros();
    newOmega = event.abs_omega;
    dOmega = newOmega - lastOmega;
    dt = now - lastTime;
    dOmegaDt = dOmega / dt;

    //Apply Torque Through Low Pass Filter
    _torque = MOI * dOmegaDt;
    torque = 0.6 * _torque + 0.3 * torque;

    if (torque > 25){
      entity.blue();
    }

    //Setup For Next Update
    lastTime = now;
    lastOmega = newOmega;
  }
