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

  State* stateNow()
  {
    return _states.back();
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
  virtual void handleInput( MotionEvent &motion ){};
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
};

class MotionState: public State, public IMotion
{
public:
  MotionState();
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

};

class Rest: public MotionState {};
class Motion: public MotionState {};
class Spin: public MotionState {};

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
  Rest restState;
  Motion motionState;
  Spin spinState;

  int currentState = REST;
  std::vector<MotionState*>  _states;
  //Important Funcitons
  virtual void initialize();
  virtual void handleInput( Event &event);
  virtual void handleInput( MotionEvent &motion );

  MotionState* stateNow()
  {
    return _states.back();
  };

};
