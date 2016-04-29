#import "application.h"
#import "patterns.h"

class State //In which we derive our actions
{
public:
  virtual ~State() {}
  virtual void handleInput( Event &event) {}
  virtual void update() {}
  virtual void enter() {}
  virtual void leave() {}
};

class Airborne: public State
{
};
