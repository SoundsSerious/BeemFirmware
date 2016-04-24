#import "application.h"
#import "mpu9250.h"

class Frisbeem //In which we combine Lights + Motion + Games
{
public:
  //States
  State _powerState;
  State _motionState;
  State _lightMode;
  State _gameMode;

  //Hardware
  int _mpu;
  Adafruit_NeoPixel _strip;

  //Connection
  TCPClient _client;
}
