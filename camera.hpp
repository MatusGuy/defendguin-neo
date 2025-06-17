#pragma once

#include <cog2d/scene/camera.hpp>
#include <cog2d/util/timer.hpp>

class Camera : public cog2d::Camera
{
public:
	Camera();

	void update() override;

private:
	cog2d::Timer m_timer;
};
