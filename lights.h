#import "application.h"
//#import "observer.h"
#import "dotstar.h"

#define DOTSTAR_GRB (1 | (0 << 2) | (2 << 4))
#define NUM_LED 54

class Lights { //public Observer
public:
  //In Which We Light The World
  Lights(): _strip( NUM_LED ){_strip.brightness = brightness;};
  ~Lights(){};

  Adafruit_DotStar _strip;
  uint8_t brightness = 100;
  
  //Counting variables
  uint8_t whl;

  //Color Functions
  void rainbow( uint8_t wait );
  void colorAll(uint32_t c, uint8_t wait);
  void colorWipe(uint32_t c, uint8_t wait);
  virtual void blue();
  virtual void green();
  virtual void red();
  virtual void off();
  uint32_t wheel( byte WheelPos );

};
