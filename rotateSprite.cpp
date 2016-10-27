#include <cmath>
#include "rotateSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL.h>

RotateSprite::RotateSprite(const std::string& name) :

  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")) 
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),//WORLD_WIDTH),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))//WORLD_HEIGHT)
{ }

RotateSprite::RotateSprite(const string& n, const Vector2f& pos, const Vector2f& vel):

  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }

RotateSprite::RotateSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):

  Drawable(n, pos, vel), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }

RotateSprite::RotateSprite(const RotateSprite& s) :

  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT"))
{ }

RotateSprite& RotateSprite::operator=(const RotateSprite&)
{
  return *this;
}


void RotateSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  double angle = 10 * SDL_GetTicks() * 0.001;
  frame->draw(x, y, angle); 
}

int RotateSprite::getDistance(const RotateSprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void RotateSprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
