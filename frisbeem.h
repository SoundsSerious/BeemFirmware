#include "application.h"
#include "mpu9250.h"
#include "lights.h"
#include "communication.h"
#include "state.h"
#include "entity.h"
#include "subject.h"
#include "event.h"

using namespace std;

//WARNING:: SPELLING MAY BE EXTREMELY BAD!!!

#define NUM_EVENTS 10

//In which we combine Lights + Motion + Games
class Frisbeem: public Subject, public Entity
{
public:
  Frisbeem(): _mpu(), _lights(), _com(){};//Constructor
  virtual ~Frisbeem() {}; //Destructor

  //Physical parameters

  //States
  StateSwitch _powerState;
  StateSwitch _motionState;
  StateSwitch _lightMode;
  StateSwitch _gameMode;

  //Hardware
  MPU_9250 _mpu;
  Lights _lights;

  //Connection
  COM _com;

  //Events
  Event *_events[ NUM_EVENTS ];
  Event newEvent = Event(0);
  uint8_t _currentEventIndex = 0;
  int _eventCount;

  //Important Entity Functions
  virtual void initlaize();
  virtual void update();

  //Sandbox Functions
  unsigned long lastTime,thisTime;
  int lightOffset = 0;
  float thetaOffset = 0;
  float degPerPixel = 360/ NUM_LED ;
  void updateThetaOffset();

  //Event Functions
  Event genNextEvent();
  Event *getCurrentEvent();
  void setCurrentEvent( Event *event );
  void processEvents();
};
