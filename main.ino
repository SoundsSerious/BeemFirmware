#import "application.h"
#import "frisbeem.h"
#include "i2c_hal.h"

Frisbeem frisbeem = Frisbeem();

#define I2C_SPEED (uint32_t)600000

void setup() {
Wire.setSpeed(I2C_SPEED);
frisbeem.initalize();

}

void loop() {

frisbeem.update();

}
