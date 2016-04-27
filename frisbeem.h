#import "application.h"
#import "mpu9250.h"
#import "dotstar.h"
#import "patterns.h"

#define DOTSTAR_GRB (1 | (0 << 2) | (2 << 4))
uint16_t PIXEL_COUNT = 54;

//In which we combine Lights + Motion + Games
class Frisbeem: public Entity, public Subject
{
public:
  Frisbeem() {}; //Constructor
  ~Frisbeem() {}; //Destructor

  //States
  State* _powerState;
  State* _motionState;
  State* _lightMode;
  State* _gameMode;

  //Hardware
  MPU_9250 _mpu = MPU_9250();
  Adafruit_DotStar _strip = Adafruit_DotStar(PIXEL_COUNT,DOTSTAR_GRB);

  //Connection
  TCPClient _client;

  //Functions
  void rainbow( uint8_t wait );
  uint32_t Wheel( byte WheelPos );

  void initalize(){
    //Update MPU
    _mpu.initlaize();
    //Update Strip
    _strip.begin();
    _strip.show();
  }

  void update(){
    //Update MPU
    _mpu.update();
    //Update Strip
    rainbow(0);
  }
};
