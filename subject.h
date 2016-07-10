#import "application.h"
#import "observer.h"

#include <vector>

#define MAX_OBSERVERS 20

class Event;
class MotionEvent;
class Game;

class ISubject
{
  virtual void notify( Event &event) = 0;
};

class Subject: public ISubject //In which we send notifications
{
public:
  ~Subject(){};

  //Observer Storage
  std::vector<Observer*>  observers_;
  int numObservers_;

  void addObserver(Observer *observer);
  //void addObserver(Game *game);

  void removeObserver(Observer &observer);
  //void removeObserver(Game &game);

  virtual void notify( Event &event);
  virtual void notify( MotionEvent &motion);
};
