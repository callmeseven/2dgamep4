#include <string>
#include "ioManager.h"
#include "frame.h"
#include "viewport.h"

class Float {
public:
  Float(const std::string& name, int fact);
  // ~World() { ; } // The frame will be deleted by the FrameFactory
  void update();
  void draw(Sint16 yyy, Sint16 yy) const;
private:
  const IOManager& io;
  Frame* const frame;
  int factor;
  unsigned frameWidth;
  unsigned worldWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  Float(const Float&);
  Float& operator=(const Float&);
};
