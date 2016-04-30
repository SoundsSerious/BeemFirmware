#import "state.h"

void StateSwitch::initialize(){
  Serial.println("Pointer Assignment");

  _states.push_back( new MotionState() );
  Serial.print("Last Item"); Serial.println( _states.back() -> msg );
}
