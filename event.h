#include "application.h"
#import "state.h"
//#import "subject.h"
//#import "observer.h"
//#include "globals.h"

class IEvent
{
  virtual void visit(State *s) =0;
};

class Event: public IEvent{
public:
  Event(){};
  ~Event() {};
  String msg;
  //Should Return The Type Of Event
  virtual void visit(State *s) { s -> handleInput(*this); }; //State
  //virtual void visit(Subject &sj) =0;//{ sj.notify(this); }; //Subject
  //virtual void visit(Observer &o) =0;//{ o.onNotify(this); }; //Observer
};

class MotionEvent: public Event
{
public:
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
