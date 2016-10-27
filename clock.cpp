#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"
#include <vector>

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock instance;
  return instance;
}


Clock::Clock() :
  frameTick(),
	frameCount(0),
	fps(0),
	one_frame_tick(0),
	old_frame_tick(0),
	tick_Diff(0),
	tick_Sum(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), 
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 
  frames(0), 
  tickSum(0),
  sumOfAllTicks(0),
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0) 
  {
  start();
}

Clock::Clock(const Clock& c) :
  frameTick(),
	frameCount(0),
	fps(0),
	one_frame_tick(0),
	old_frame_tick(0),
	tick_Diff(0),
	tick_Sum(0),

  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  framesAreCapped(c.framesAreCapped), 
  frameCap(c.frameCap), 
  frames(c.frames),
  tickSum(c.tickSum),
  sumOfAllTicks(c.sumOfAllTicks),
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks) 
  {
  start();
}

void Clock::display() const { 
 // static unsigned int lastFrames = 0;
  //static unsigned int oldFrames = 0;
  static unsigned int seconds = getSeconds();

  if ( getSeconds() > seconds ) {
    seconds = getSeconds();
   // lastFrames = frames - oldFrames;
    //oldFrames = frames;
  }
  //IOManager::getInstance()
    //.printMessageValueAt("seconds: ", seconds, 10, 30);
  //IOManager::getInstance()
  //  .printMessageValueAt("frames in sec: ", lastFrames, 10, 50);
    //IOManager::getInstance().printMessageValueAt("fps: ", getFps(), 10, 30);
}

void Clock::toggleSloMo() {
  if( started && !sloMo ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    sloMo = true;
  }
  else if ( started && sloMo ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    sloMo = false;
  }
}

unsigned int Clock::getTicks() const { 
  if (paused) return timeAtPause;
  else if ( sloMo ) return 1;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned int Clock::getElapsedTicks() { 
  if (paused) return 0;
  else if ( sloMo ) return 1;

  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  unsigned int delay = capFrameRate();
  prevTicks = currTicks + delay;
  ticks += delay;
  sumOfAllTicks += ticks;
  return ticks;
}

unsigned int Clock::capFrameRate() const { 
  if ( !framesAreCapped ) return 0u;
  unsigned int delay = std::max(0.0,1000.0/frameCap+0.5 - ticks);
  SDL_Delay( delay );
  return delay;
}

Clock& Clock::operator++() { 
  if ( !paused ) {
    ++frames; 
  }
  return *this;
}

void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

//extend clock class so that to print fps

int Clock::getFps()
{
	if (frameCount <= FPS_MAX+5)
{
	one_frame_tick = SDL_GetTicks() - old_frame_tick;
	old_frame_tick = SDL_GetTicks();
	frameTick.push_back(one_frame_tick);
	tick_Sum = tick_Sum + one_frame_tick;
	fps = 1000 * frameCount / tick_Sum;
	frameCount++;
	return fps;
}

else
{
	one_frame_tick = SDL_GetTicks() - old_frame_tick;
	old_frame_tick = SDL_GetTicks();
	tick_Diff = one_frame_tick - frameTick[frameCount%FPS_MAX];
	tick_Sum  = tick_Sum + one_frame_tick - frameTick[frameCount%FPS_MAX];
	frameTick[frameCount%FPS_MAX] = one_frame_tick;
	fps = 1000 * FPS_MAX / tick_Sum;
	frameCount++;
	return fps;
}
}
