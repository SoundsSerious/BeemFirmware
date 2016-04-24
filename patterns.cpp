#import "patterns.h"


class Subject
{
  public:
    void addObserver(Observer* observer)
    {
      if ( numObservers_ < MAX_OBSERVERS -1){
        inx = numObservers_+1;
        observers_[inx] = observer;
        observer._index = inx;
        numObservers_ += 1;
      }
    }

    void removeObserver(Observer* observer)
    {
         inx = observer._index;
         for(i = inx; i < MAX_OBSERVERS - 1; i++) observers_[i] = observers_[i + 1];
         numObservers_ -= 1;
    }

  void notify(const Entity& entity, Event event)
  {
    for (int i = 0; i < numObservers_; i++)
    {
      observers_[i]->onNotify(entity, event);
    }
  }
};
