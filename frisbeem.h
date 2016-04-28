#import "application.h"
#import "mpu9250.h"
#import "dotstar.h"
#import "patterns.h"

#define DOTSTAR_GRB (1 | (0 << 2) | (2 << 4))
//uint16_t LEDS = 54;

//In which we combine Lights + Motion + Games
class Frisbeem: public Entity, public Subject
{
public:
  Frisbeem(): _mpu(), _strip(54){};//Constructor
  ~Frisbeem() {}; //Destructor

  //States
  State* _powerState;
  State* _motionState;
  State* _lightMode;
  State* _gameMode;

  //Hardware
  MPU_9250 _mpu;
  Adafruit_DotStar _strip;

  //Connection
  TCPClient _client;

  //Counting variables
  uint8_t whl;

  //Functions
  void rainbow( uint8_t wait );
  void colorAll(uint32_t c, uint8_t wait);
  void colorWipe(uint32_t c, uint8_t wait);
  void blue();
  uint32_t Wheel( byte WheelPos );


  void initalize(){
    //Update MPU
    _mpu.initlaize();
    //Update Strip
    _strip.begin();
    _strip.show();
  }

  void update(){
    //Serial.println("Update");
    //Update MPU
    _mpu.update();
    //Update Strip
    this -> rainbow(5);
  }
};
