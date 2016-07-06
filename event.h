#include "application.h"
#include "3dmath.h"

//Fwd Declaration
class State;
class Subject;
class Observer;
class StateSwitch;

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
  MotionEvent( VectorFloat &Gin, VectorFloat &Ain, VectorFloat &Vin, VectorFloat &Xin);
  ~MotionEvent(){};

  virtual String type() {return "MotionEvent";};

  //Should Return The Type Of Event
  virtual void visit(State *s); //State
  virtual void visit(Subject *sj); //Subject
  virtual void visit(Observer *o); //Observer
  virtual void visit(StateSwitch *s); //State

  VectorFloat G,A,V,X;
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
