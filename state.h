#import "application.h"
#undef min
#undef max
#include <vector>
#import "event.h"
#import "colors.h"

#define MAX_STATES 50 //'Murica
float MOI = 0.008748; //Frisbeem Moment Of Inertia

class State //In which we derive our actions
{
public:
  virtual ~State() {};
  int handleInput( Event &event ) {return 0;};
  virtual void update(){};
  virtual void enter(){};
  virtual void leave(){};

  String msg = "state";
};


//Initial States
//Airborne Transition If GYZ is greater than 450
//Stationary If GYZ is less than 10
//

class MotionState: public State
{
public:
  //Physical Values
  unsigned long lastTime = micros();
  unsigned long now = micros();
  unsigned long dt;

  float lastOmega;
  float newOmega;
  float dOmegaDt,dOmega;
  float torque, _torque;


  String msg = "motionState";

  int handleInput(Event &event)
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
      blue();
    }

    //Setup For Next Update
    lastTime = now;
    lastOmega = newOmega;
  }
};


class StateSwitch: public State
{
  //Class that passes argument to current state
public:
  int currentState = 0;
  std::vector<MotionState*>  _states;
  void initialize();

  int handleInput( Event &event)
  { Serial.println("Switch Handiling Input");
    Serial.println( _states.back() -> handleInput( event ) );
    return 0;
  }
  //Not Implemented Yet
  virtual void update() {
    _states[ currentState ] -> update();
  }
  virtual void enter() {
    _states[ currentState ] -> enter();
  }
  virtual void leave() {
    _states[ currentState ] -> leave();
  }

};
