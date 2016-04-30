#import "application.h"
#undef min
#undef max
#include <vector>
#import "event.h"
#import "entity.h"

using namespace std;

#define MAX_STATES 50 //'Murica
//float MOI = 0.008748; //Frisbeem Moment Of Inertia

class State //In which we derive our actions
{
public:
  virtual ~State() {};
  virtual int handleInput(Entity &entity, Event &event ) {return 0;};
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

  virtual int handleInput(Entity &entity, Event &event);
};


class StateSwitch: public State
{
  //Class that passes argument to current state
public:
  int currentState = 0;
  std::vector<MotionState*>  _states;
  void initialize();

  virtual int handleInput(Entity &entity, Event &event)
  { Serial.println("Switch Handiling Input");
    Serial.println( _states.back() -> handleInput( entity, event ) );
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
