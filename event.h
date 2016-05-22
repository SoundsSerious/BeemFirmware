#include "application.h"
//#include "globals.h"

class Event{
public:
  ~Event() {};
  //Should Return The Type Of Event
  virtual String type() = 0;
  virtual float data() = 0;
  virtual String msg() = 0;
};

class MotionEvent: public Event {
public:
  MotionEvent(float omega){abs_omega = abs(omega);};
  float abs_omega;
  virtual String type();
  virtual float data();
  virtual String msg(){return "";};
};


class COMEvent: public Event {
public:
  COMEvent(String message){message = message;};
  String message;
  virtual String type();
  virtual float data(){return 0;};
  virtual String msg();
};
