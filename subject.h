#import "application.h"
#import "observer.h"

#define MAX_OBSERVERS 20

class Event;

class ISubject
{
  virtual void notify( Event &event) = 0;
};

class Subject: public ISubject //In which we send notifications
{
public:
  ~Subject(){};

  //Observer Storage
  Observer *observers_[MAX_OBSERVERS];
  int numObservers_;
  void addObserver(Observer &observer);
  void removeObserver(Observer &observer);
  virtual void notify( Event &event);
};
