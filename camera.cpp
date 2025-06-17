#include "camera.hpp"

#include <cog2d/util/logger.hpp>

Camera::Camera()
    : cog2d::Camera()
{
}

void Camera::update()
{
	if (!m_timer.started())
		m_timer.start(1500);

	if (m_timer.check()) {
		m_pos.x += 16;
		COG2D_LOG_DEBUG(cog2d::fmt::format("campos: {}", m_pos));
	}
}
