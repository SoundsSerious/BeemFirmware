#include "application.h"

class Event{
  public:
  Event(float omega){abs_omega = omega;};
  ~Event() {};
  float abs_omega;
};
