#ifndef ROTATESPRITE__H
#define ROTATESPRITE__H
#include <string>
#include "drawable.h"

class RotateSprite : public Drawable {
public:
  RotateSprite(const std::string&);
  RotateSprite(const RotateSprite& s);
  RotateSprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  RotateSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  RotateSprite& operator=(const RotateSprite&);
  virtual ~RotateSprite() { } 

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;

  virtual void update(Uint32 ticks);

private:
  const Frame * frame;

  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const RotateSprite*) const;
};
#endif
