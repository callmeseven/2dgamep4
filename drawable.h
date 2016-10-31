#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include <cmath>
#include "vector2f.h"
#include "frame.h"
 
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel): 
    name(n), position(pos), velocity(vel), direction(true) , zoom( (rand()%30+10)/20) {}  
 // Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, double& zoom):name(n), position(pos), velocity(vel), zoom_scale(zoom) 
    //{ }

  Drawable(const Drawable& s) : 
    name(s.name), position(s.position), velocity(s.velocity), direction(s.direction), zoom(s.zoom)   { }

  virtual ~Drawable() {}

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }
  virtual const Frame* getFrame() const = 0;

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float X() const { return position[0]; }
  void X(float x) { position[0] = x;    }

  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y;    }

  float velocityX() const  { return velocity[0]; }
  void velocityX(float vx) { velocity[0] = vx;   }
  float velocityY() const  { return velocity[1]; }
  void velocityY(float vy) { velocity[1] = vy;   }

  bool direct() const { return direction; }
  void direct(bool n) { direction = n;}

  double getzoom() const { return zoom; }
  void getzoom( double n) { zoom = n;}
  
  double getAbsV() { return sqrt((velocity[0]*velocity[0])+(velocity[1])*velocity[1]); }
  const Vector2f& getVelocity() const   { return velocity; }
  void setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const   { return position; }
  void setPosition(const Vector2f& pos) { position = pos;  }

  virtual bool collidedWith(const Drawable*) const { 
    throw std::string("No collidedWith");  
  }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  bool direction;
  double zoom;
};
#endif
