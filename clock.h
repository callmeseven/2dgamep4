#include <SDL.h>
#include <string>
#include "gamedata.h"
#include <vector>

class Manager;

static const int FPS_MAX = Gamedata::getInstance().getXmlInt("FPS_MAX");

class Clock {
public:
 
  static Clock& getInstance(); //--------------------singleton change to meyers
  unsigned int getTicks() const;
  unsigned int getTotalTicks() const { return sumOfAllTicks; }
  int getFps() ;


private:
  friend class Manager;
  //static Clock instance;


  // my new var-------------------
  std::vector<unsigned int> frameTick; 
  int frameCount;
  int fps;
  unsigned int one_frame_tick;
  unsigned int old_frame_tick;  
  int tick_Diff;
  unsigned int tick_Sum;
  //-------------------------------
  bool started;
  bool paused;
  bool sloMo;
  const bool framesAreCapped;
  const int frameCap;

  unsigned int frames;

  unsigned int tickSum;
  unsigned int sumOfAllTicks;
  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;

  unsigned int getElapsedTicks();
  Clock& operator++();
  void toggleSloMo();

  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned int getFrames() const  { return frames;  }
  unsigned int getSeconds() const { return getTicks()/1000;  }
  unsigned int capFrameRate() const;

  void start();
  void pause();
  void unpause();
  void display() const;

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);



};
