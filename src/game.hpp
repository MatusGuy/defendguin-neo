#pragma once

#include <cog2d/ecs/world.hpp>
#include <cog2d/tilemap/tilemap.hpp>

#include "entity.hpp"

namespace game {

extern cog2d::World<Entity> world;
extern cog2d::TileMap tilemap;

void init();
void draw();
void update();

}  //namespace game
