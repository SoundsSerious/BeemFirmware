#include "games.h"
#include "globals.h"

void Firework::onNotify( MotionEvent &motion)
{
  frisbeem._com.log("Firework Notified");
  //Check New Data To See Parse Informatoin
  if ( motion.G.z > 300)
  {
    //Check Height:
    //If Height is greater than the max, set maxHeight
    //otherwise
    if ( motion.X.z > maxHeight )
    {
      maxHeight = motion.X.z;
    }
    else
    {
      //Check Velocity:
      //If Velocity Is Negative In Z and a max has not been detected
      //Set Flag & Send Signal
      if ( motion.V.z < 0 && !peakDetected){
        peakDetected = true;
        //If There's a good increase in altitude... lets play a sound
        if (maxHeight > 2){ frisbeem._com.sendCommand("AUD","PLY","BNG"); }
      }
    }
  }
  else{
    //Not Spinning
    maxHeight = 0;
    peakDetected = false;
  }

}

void Firework::update()
{
  frisbeem._com.log("Updating Firework Game");

  //Check If Peak Conditions Are Met... Then Send A Signal
}
