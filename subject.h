#import "application.h"
#import "observer.h"
#define MAX_OBSERVERS 20

class Subject //In which we send notifications
{
public:
  Observer* observers_[MAX_OBSERVERS];
  int numObservers_;
  void addObserver(Observer &observer);
  void removeObserver(Observer &observer);
  void notify(const Entity &entity, Event &event);
};
