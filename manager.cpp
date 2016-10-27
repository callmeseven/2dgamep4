#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "rotateSprite.h"
#include "gamedata.h"
#include "manager.h"
#include "aaline.h"
#include "ioManager.h"

unsigned int hud_on_time;

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  //tree("tree",Gamedata::getInstance().getXmlInt("tree/factor")),
  mount("mount", Gamedata::getInstance().getXmlInt("mount/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  fps(0)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.push_back( new MultiSprite("pacman") );
  //sprites.push_back( new MultiSprite("bluepac1") );
  //sprites.push_back( new RotateSprite("coologo") );
  //sprites.push_back( new MultiSprite("bluepac2") );
  //sprites.push_back( new Sprite("sillyman1") );
  //sprites.push_back( new Sprite("sillyman2") );
  //sprites.push_back( new Sprite("sillyman3") );
  //sprites.push_back( new Sprite("greenorb") );
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void drawBackground(SDL_Surface* screen)
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,255,255));
    SDL_Rect dest = {0,0,0,0};
    SDL_BlitSurface(screen, NULL,screen, &dest);
}

void Manager::display_hud(SDL_Surface* screen, const Uint32 RED, int fps)
{
    SDL_Rect rect = {10,10,170,160};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255,255,255));
    SDL_Rect dest = {10, 10, 170,160};
    SDL_BlitSurface(screen, &rect ,screen,&dest);
            Sint16 y1 = 10;
            Sint16 x1 = 10, x2 = 180;
            // draw the top line
            Draw_AALine(screen, x1, y1, x2, y1, 2.0f, RED);
            
            Draw_AALine(screen, x1, y1+160, x2, y1+160, 2.0f, RED);
            
            Draw_AALine(screen, x2, y1, x2, y1+160, 2.0f, RED);

            Draw_AALine(screen, x1, y1, x1, y1+160, 2.0f, RED);

  io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  io.printMessageValueAt("fps: ", fps, 10, 40);
  io.printMessageAt("Press T to switch sprites", 10, 60);
  io.printMessageAt(title, 10, 450);
}




void Manager::draw() {
  world.draw();
  
  mount.draw(-50,280);
  //tree.draw(-50,0);
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  viewport.draw();

  //SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update(int &fps) {
  ++(clock);
  Uint32 ticks = clock.getElapsedTicks();

  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }

  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  world.update();

   mount.update();
  // tree.update();
  viewport.update(); // always update viewport last
  fps = clock.getFps();
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  bool hud_on = true;
  bool first_time_hud = true;
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0,0);


  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_F1] ) {
            if(hud_on != true)
            {
                hud_on = true;
                //hud_on_time = SDL_GetTicks();
            }
            else
            {
                hud_on = false;
            }
        }

        if ( keystate[SDLK_s] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
      }
    }
    draw();
    update(fps);
    if( hud_on != false ) 
    {
        display_hud(screen,RED,fps);
        if(first_time_hud)         //- hud_on_time > 2000)
            if ( SDL_GetTicks() > 2000 ) 
            {
            hud_on = false;
            first_time_hud = false;
            }
    }
    SDL_Flip(screen);
   // update();
  }

}
