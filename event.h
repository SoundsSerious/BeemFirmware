#include "application.h"
#include "state.h"
#include "subject.h"
//#import "observer.h"
//#include "globals.h"

//Predeclare this... need to use reference for values tho
class VectorFloat;

class IEvent
{
  virtual void visit(State *s) =0;
  virtual void visit(Subject *sj) = 0;
  virtual void visit(Observer *o) =0;
  virtual void visit(StateSwitch *s) =0; //State

  virtual String type()=0;
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
  virtual void visit(StateSwitch *s); //State

  virtual String type() {return "Event";};
};

class MotionEvent: public Event
{
public:
  MotionEvent(){};
  MotionEvent( VectorFloat &Gin, VectorFloat &Ain, VectorFloat &Vin, VectorFloat &Xin );
  ~MotionEvent(){};

  virtual String type() {return "MotionEvent";};

  //Should Return The Type Of Event
  virtual void visit(State *s); //State
  virtual void visit(Subject *sj); //Subject
  virtual void visit(Observer *o); //Observer
  virtual void visit(StateSwitch *s); //State

  //These will need to be used in the same inner loop..
  VectorFloat G, A, V, X;
};


class COMEvent: public Event {
public:
  COMEvent(String newMessage){message = newMessage;};
  ~COMEvent(){};

  virtual String type() {return "COMEvent";};

  //Should Return The Type Of Event
  virtual void visit(State *s); //State
  virtual void visit(Subject *sj); //Subject
  virtual void visit(Observer *o); //Observer
  virtual void visit(StateSwitch *s); //State

  String message;
};
