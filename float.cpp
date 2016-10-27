#include <iostream>
#include "float.h"
#include "frameFactory.h"

Float::Float(const std::string& name, int fact) : 
  io( IOManager::getInstance() ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  factor(fact),
    frameWidth( frame->getWidth() ),
    worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{}

void Float::update() {
  viewX = static_cast<int>(view.X() / factor) % frameWidth;
  viewY = view.Y();
}

void Float::draw(Sint16 yyy, Sint16 yy) const { 
  frame->draw(viewX, yyy, 0,yy); 
  frame->draw(0,yyy, frameWidth-viewX, yy); 
}

