#import "application.h"

class Event;

class IObserver //In which we notify
{
public:
  virtual void onNotify( Event& ) = 0;
};

class Observer: public IObserver
{
public:
  virtual ~Observer() {};
  virtual void onNotify( Event& ){ };
  uint8_t _index;
};
