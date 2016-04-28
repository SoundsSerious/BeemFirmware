#import "application.h"

#define MAX_OBSERVERS 20

class Entity
{
public:
  Entity()
  : x_(0), y_(0), z_(0)
  {}

  ~Entity() {}
  virtual void update() {};
  virtual void initalize() {};

  float x() const { return x_; }
  float y() const { return y_; }
  float z() const { return z_; }

  void setX(float x) { x_ = x; }
  void setY(float y) { y_ = y; }
  void setZ(float z) { z_ = z; }

  float x_;
  float y_;
  float z_;
};

class Event{

};

class Observer //In which we notify
{
public:
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
  virtual void handleInput( Event event) {}
  virtual void update() {}
  virtual void enter() {}
  virtual void leave() {}
};
