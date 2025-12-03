#ifndef COG2DINTRO_HPP
#define COG2DINTRO_HPP

#include <cog2d/util/timer.hpp>
#include <cog2d/assets/assetmanager.hpp>
#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/video/graphicsengine.hpp>

namespace intro_cog2d {

void init();
void update();
void draw();
bool event(SDL_Event* ev);

}  //namespace intro_cog2d

#endif  // COG2DINTRO_HPP
