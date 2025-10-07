#include "camera.hpp"

#include <cog2d/util/logger.hpp>

Camera::Camera()
    : cog2d::Camera()
{
}

void Camera::update()
{
	cog2d::Camera::pre_update();

	/*
	if (!m_timer.started())
	    m_timer.start(250);

	if (m_timer.check()) {
	    m_pos.x += 4;
		cog2d::log::debug(cog2d::fmt::format("campos: {}", m_pos));
	}
	*/

	m_pos.x += 1.f;

	cog2d::Camera::post_update();
}
