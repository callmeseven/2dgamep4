#include "player.h"
#include "gamedata.h"
#include "frameFactory.h"


//--------------------------------------------------------

//FOR PACMAN----------------
//------------------------------------
void Player::advanceFrame(Uint32 ticks)
{
    timeSinceLastFrame += ticks;
    if (direct())
    {
        if( timeSinceLastFrame > frameInterval )
        {
            currentFrame = (currentFrame+1) % (numberOfFrames /2);
            timeSinceLastFrame = 0;
        }
    }
    else if (!direct())
    {
        if( timeSinceLastFrame > frameInterval )
        {
            currentFrame = ((currentFrame+1) % (numberOfFrames /2)) + (numberOfFrames /2 );
            timeSinceLastFrame = 0;
        }
    }


}
//-----------------------------------------------------------

//------------------------------------------------------------
//ORIGINAL
//-----------------------------------------------------------
Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("WORLD_WIDTH")),
  worldHeight(Gamedata::getInstance().getXmlInt("WORLD_HEIGHT")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }
Player::Player(const Player& s) :
  Drawable(s), 
   // direct(s.direct),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void Player::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

 /* if ( Y() < 0) {
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
*/
}
