#import "application.h"

class Entity
{
public:
  ~Entity(){};
  virtual void update();
  virtual void initalize();

  float x() const { return x_; }
  float y() const { return y_; }
  float z() const { return z_; }

  void setX(float x) { x_ = x; }
  void setY(float y) { y_ = y; }
  void setZ(float z) { z_ = z; }

  virtual void blue();

  float x_=0;
  float y_=0;
  float z_=0;
};
