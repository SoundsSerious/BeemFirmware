#include "event.h"

void Event::visit(State *s) { s -> handleInput(*this); }; //State
void Event::visit(Subject *sj) { sj -> notify(*this); }; //Subject
void Event::visit(Observer *o) { o -> onNotify(*this); }; //Observer
void Event::visit(StateSwitch &s){ s.handleInput(*this); }; //State
