#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "float.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();
  void display_hud(SDL_Surface* screen, const Uint32 RED, int fps);

private:
  const bool env;
  const IOManager& io;
  Clock clock;

  SDL_Surface * const screen;
  World world;
//  Float tree;
  Float mount;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw();
  void update(int &fps);
  int fps;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
