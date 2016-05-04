#include "application.h"

class Event{
  public:
  Event(float omega){abs_omega = abs(omega);};
  ~Event() {};
  float abs_omega;
};
