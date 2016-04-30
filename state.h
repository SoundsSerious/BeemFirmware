#import "application.h"
#import "event.h"
#define MAX_STATES 50 //'Murica

class State //In which we derive our actions
{
public:
  virtual ~State() {};
  virtual void handleInput( Event &event) {};
  virtual void update() {};
  virtual void enter() {};
  virtual void leave() {};
};

class StateSwitch: public State
{
  //Class that passes argument to current state
public:
  uint8_t currentState;
  State *_states[MAX_STATES];

  virtual void handleInput( Event &event)
  {
    _states[ currentState ] -> handleInput( event );
  }
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

//Initial States

class MotionState: public State
{
  float lastOmega
  float torque
};
