import "application.h"

#define MAX_OBSERVERS = 20

class Observer //In which we notify
{
public:
  int _index = NULL;
  virtual ~Observer() {}
  virtual void onNotify(const Entity& entity, Event event) = 0;
};

class Subject //In which we send notifications
{
public:
  Observer* observers_[MAX_OBSERVERS];
  int numObservers_;
  void addObserver(Observer* observer) {}
  void removeObserver(Observer* observer) {}
  void notify(const Entity& entity, Event event) {}
};

class State //In which we derive our actions
{
public:
  virtual ~State() {}
  virtual void handleInput(Frisbeem& frisbeem, Input input) {}
  virtual void update(Frisbeem& frisbeem) {}
  virtual void enter(Frisbeem& frisbeem) {}
  virtual void leave(Frisbeem& frisbeem) {}
};
