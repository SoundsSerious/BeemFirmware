#import "application.h"
#import "event.h"
#import "entity.h"


class Observer //In which we notify
{
public:
  virtual ~Observer() {};
  virtual void onNotify( Event &event) = 0;
  uint8_t _index;
};
