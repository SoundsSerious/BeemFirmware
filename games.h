#include "application.h"
#include "observer.h"

//Predeclare
//class Observer;
class Event;
class MotionEvent;
class COMEvent;

class Game: public Observer
{
public:
  //virtual Several Types Of Events As Notificaitons
  virtual void onNotify( Event &event){};
  virtual void onNotify( MotionEvent &motion){};
  virtual void onNotify( COMEvent &com){};

  //Important Methods
  virtual void update(){};
  virtual String name() {return "Game";};
};

class Firework: public Game
{
public:
  //Important Methods
  virtual void onNotify( Event &motion){};
  virtual void onNotify( MotionEvent &motion);
  virtual void update();

  //Peak Detection
  //If the disk is spinning, check throwHeight against the currentMax
  //If height is less than the maxHeight, and postMaxVelocity is negative
  //Send Out A PeakThrow Signal That Lights An Animation & Plays a sound
  float maxHeight;
  bool isSpinning;
  bool peakDetected;

  virtual String name() {return "Firework";};
};
