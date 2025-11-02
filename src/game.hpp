#pragma once

#include <cog2d/ecs/world.hpp>

#include "entity.hpp"

namespace game {

extern cog2d::World<Entity> world;

void init();
void draw();
void update();

}  //namespace game
