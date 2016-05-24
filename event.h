#include "application.h"
#import "state.h"
#import "subject.h"
//#import "observer.h"
//#include "globals.h"

class IEvent
{
  virtual void visit(State *s) =0;
  virtual void visit(Subject *sj) = 0;
  virtual void visit(Observer *o) =0;
  virtual void visit(StateSwitch &s) =0; //State

};

class Event: public IEvent{
public:
  Event(){};
  ~Event() {};
  String msg;
  //Should Return The Type Of Event
  virtual void visit(State *s); //State
  virtual void visit(Subject *sj); //Subject
  virtual void visit(Observer *o); //Observer
  virtual void visit(StateSwitch &s); //State
};

class MotionEvent: public Event
{
public:
  MotionEvent(){abs_omega = 0.0;};
  MotionEvent( float omega ){abs_omega = abs(omega);};
  ~MotionEvent(){};
  float abs_omega;
};


class COMEvent: public Event {
public:
  COMEvent(String newMessage){message = newMessage;};
  ~COMEvent(){};
  String message;
};
