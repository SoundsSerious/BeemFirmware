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

//In which we combine Lights + Motion + Games
class Frisbeem: public Subject, public Entity
{
public:
  Frisbeem(): _mpu(), _lights(), _com(){};//Constructor
  virtual ~Frisbeem() {}; //Destructor (of doooom)

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
  MotionEvent currentMotionEvent = MotionEvent(0.0);
  //Event Functions
  MotionEvent genNextEvent();
  void processMotion();

  //Important Entity Functions
  virtual void initlaize();
  virtual void update();

  //Sandbox Functions
  unsigned long lastTime,thisTime;
  int lightOffset = 0;
  float thetaOffset = 0;
  float degPerPixel = 360/ NUM_LED ;
  void updateThetaOffset();


};
