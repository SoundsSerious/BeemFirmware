#import "subject.h"
#import "observer.h"

void Subject::addObserver(Observer  &observer)
{
  if ( numObservers_ < MAX_OBSERVERS -1){
    int inx = numObservers_+1;
    observers_[inx] = &observer;
    observer._index = inx;
    numObservers_ += 1;
  }
}

void Subject::removeObserver(Observer &observer)
{     //Shift Down Other Observers
     int inx = observer._index;
     for( int i = inx; i < MAX_OBSERVERS - 1; i++) observers_[i] = observers_[i + 1];
     numObservers_ -= 1;
}

void Subject::notify(Entity &entity, Event &event)
{
  for (int i = 0; i < numObservers_; i++)
  {
    observers_[i]->onNotify(entity, event);
  }
}
