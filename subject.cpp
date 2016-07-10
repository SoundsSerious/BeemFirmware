#import "subject.h"
#import "globals.h"
#import "games.h"

void Subject::addObserver(Observer  *observer)
{
  frisbeem._com.log("Adding Observer " + observer -> name());
  observers_.push_back(observer);
  numObservers_+=1;
  frisbeem._com.log("Added To List");
}

// void Subject::addObserver(Game *game)
// {
//   frisbeem._com.log("Adding Game " + game -> name);
//   if ( numObservers_ < MAX_OBSERVERS -1){
//     int inx = numObservers_+1;
//     observers_.at(inx) = game;
//     game -> _index = inx;
//     numObservers_ += 1;
//   }
// }

void Subject::removeObserver(Observer &observer)
{     //Shift Down Other Observers
     int inx = observer._index;
     for( int i = inx; i < MAX_OBSERVERS - 1; i++) observers_.at(i) = observers_.at(i+1);
     numObservers_ -= 1;
}


void Subject::notify(Event &event)
{
  for (int i = 0; i < observers_.size(); i++)
  {
    frisbeem._com.log("Notifying Event");
    observers_.at(i)->onNotify( event );
  }
}

void Subject::notify(MotionEvent &motion)
{
  for (int i = 0; i < observers_.size(); i++)
  {
    frisbeem._com.log("Notifying Motion Event");
    observers_.at(i)->onNotify( motion );
  }
}
