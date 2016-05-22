#include "event.h"

String MotionEvent::type(){
  return "MotionEvent";
}

float MotionEvent::data(){
  return this -> abs_omega;
}

String COMEvent::type(){
  return "COMEvent";
}

String COMEvent::msg(){
  return message;
}
