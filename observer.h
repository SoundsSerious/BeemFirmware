#import "application.h"

class Event;
class MotionEvent;
class COMEvent;

class IObserver //In which we notify
{
public:
  virtual void onNotify( Event &event) = 0;
  virtual String name() = 0;
};

class Observer: public IObserver
{
public:
  virtual ~Observer() {};
  virtual void onNotify( Event &event ){};
  virtual void onNotify( MotionEvent &motion){};
  virtual void onNotify( COMEvent &com){};
  uint8_t _index;

  virtual String name() {return "Observer";};
};
