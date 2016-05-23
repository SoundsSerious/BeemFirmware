#include "application.h"
//#import "state.h"
//#import "subject.h"
//#import "observer.h"
//#include "globals.h"
enum EVENT_TYPES{
  MOTIONEVENT,
  COMEVENT,
};

class Event{
public:
  Event(){};
  ~Event() {};
  float data;
  //Should Return The Type Of Event
  //virtual void visit(State &s) =0;//{ s.handleInput(*this); }; //State
  //virtual void visit(Subject &sj) =0;//{ sj.notify(this); }; //Subject
  //virtual void visit(Observer &o) =0;//{ o.onNotify(this); }; //Observer
};

class MotionEvent: public Event {
public:
  MotionEvent(float omega){abs_omega = abs(omega);};
  float abs_omega;
};


class COMEvent: public Event {
public:
  COMEvent(String message){message = message;};
  String message;
};
