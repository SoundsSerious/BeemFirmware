#import "application.h"
#import "dotstar.h"

#define DOTSTAR_GRB (1 | (0 << 2) | (2 << 4))
#define NUM_LED 50

class Lights
{ //In Which We Light The World
public:
  Lights(): _strip( NUM_LED ){_strip.brightness = brightness;};
  ~Lights(){};

  bool _on = true;
  bool show = true;
  
  Adafruit_DotStar _strip;
  uint8_t brightness = 100;

  //Counting variables
  uint8_t whl;

  //Important Funcitons
  virtual void update(uint8_t wait);
  virtual void initlaize();
  void refresh();

  //Color Functions
  void rainbow( uint8_t offset);
  void colorAll(uint32_t c);
  void colorWipe(uint32_t c, uint8_t wait);
  void quarters(uint32_t c,uint32_t c2, uint8_t offset);

  //Solid Colors
  virtual void blue();
  virtual void green();
  virtual void red();
  virtual void off();

  //Utility Functions
  uint32_t wheel( byte WheelPos );

};
