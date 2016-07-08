#include"application.h"
#undef min
#undef max
#include <vector>
#import "3dmath.h"
//using namespace std;

//Predeclare
class Event;
class MotionEvent;
//class VectorFloat;

#define MAX_STATES 50 //'Murica

////////////////////////////////////////////////////////////////////////////////
//GENERAL STATES
////////////////////////////////////////////////////////////////////////////////
class IState
{
public:
  virtual void handleInput( Event &event ) = 0;
  //virtual void handleInput( MotionEvent &event ) = 0;
  virtual String type() = 0;
};


class State: public IState //In which we derive our actions
{
public:
  State() {};
  virtual ~State() {};
  //Override handleInput for visitor pattern
  virtual void handleInput( Event &event ){};

  //Other Important Functions
  virtual void update(){};
  virtual void enter(){};
  virtual void leave(){};

  virtual String type() {return "state";};
};

//Container For Many States
class StateSwitch: public State
{
  //Class that passes argument to current state
public:
  StateSwitch(){ initialize(); };
  ~StateSwitch(){};

  int currentState = 0;
  std::vector<State*>  _states;
  //Important Funcitons
  virtual void initialize(){};
  virtual void handleInput( Event &event);

  virtual String type() {return "StateSwitch";};

  virtual State* stateNow()
  {
    return _states.at(currentState);
  };
  //Not Implemented Yet
  virtual void update() {
    _states[ currentState ] -> update();
  };
  virtual void enter() {
    _states[ currentState ] -> enter();
  };
  virtual void leave() {
    _states[ currentState ] -> leave();
  };

};

////////////////////////////////////////////////////////////////////////////////
//MOTION STATES
////////////////////////////////////////////////////////////////////////////////
class IMotion //Interface. Motion States Should Take Motion Events
{
public:
  virtual void handleInput( MotionEvent &motion )=0;
};

//Persistant Object To Share Among Substates
class MotionData
{ public:
  //Motion State Should Track Generalized Values Among All States
  //Last Update Time
  unsigned long lastTime = micros();
  unsigned long now = micros();
  unsigned long dt;

  //Spin threshold
  float spinThreshold = 200;

  //Bullshit For Functionality... send out to other classes
  int stationaryCount;
  bool moving = false;
  bool sleepModeActivated = false;
  unsigned long sleepThreshold = 15000;
  unsigned long stationaryReset = -10;

  //Torque Parameters
  float dOmegaDt, _torque, torque, dOmega, newOmega, lastOmega;
  String msg = "Hello is motion";
};

class MotionState: public State, public IMotion
{
public:
  MotionState() ;
  ~MotionState(){};
  //Slot For MotionData Object
  MotionData *_motionData;
  MotionEvent *_motionEvent;

  //Override handleInput for visitor pattern
  virtual void handleInput( Event &event ){};
  virtual void handleInput( MotionEvent &motion );

  //Other Important Functions
  virtual void update();
  virtual void enter(){};
  virtual void leave(){};

  //Store Last Values
  VectorFloat Glast, Alast, Vlast, Xlast;

  //Need To Define Method All Event Types... C++ cannot double dispatch so
  //It helps to overload the state event handlers... it can't do both at once
  virtual String type() {return "MotionState";};
  String msg = "Hello Is Motion";
};

class RestState: public MotionState{virtual String type() {return "RestState";};};
class DynamicMotionState: public MotionState{virtual String type() {return "DynamicMotionState";};};
class SpinState: public MotionState{virtual String type() {return "SpinState";};};

class MotionSwitch: public StateSwitch, public IMotion
{
public:
  MotionSwitch(){ initialize(); };
  ~MotionSwitch(){};

  //Sub States Should Be In this Order
  enum MotionStates {
    REST = 0,
    MOTION,
    SPIN,
  };

  //Make Motion States
  RestState restState;
  DynamicMotionState motionState;
  SpinState spinState;

  int currentState = REST;

  //Watchout! Defining This Outside of a default constructor can cause invalid pointers
  //to be stored.
  std::vector<MotionState*>  _states;

  //Important Funcitons
  virtual void initialize();
  virtual void handleInput( Event &event);
  virtual void handleInput( MotionEvent &motion );
  virtual MotionState * stateNow();

  virtual String type() {return "MotionSwitch";};

  //Not Implemented Yet
  virtual void update() {
    _states[ currentState ] -> update();
  };
  virtual void enter() {
    _states[ currentState ] -> enter();
  };
  virtual void leave() {
    _states[ currentState ] -> leave();
  };

};
