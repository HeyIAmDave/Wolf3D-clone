#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_pos(0), m_rot({0, 0, 0}), m_scale(1)
{ }

void Transform::Rotate(float angle, const glm::vec3 & axis)
{
	m_rot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

glm::mat4 Transform::CreateModelMatrix() const
{
	glm::mat4 t = glm::translate(glm::mat4(1.0f), m_pos);
	glm::mat4 r = glm::mat4_cast(m_rot);
	glm::mat4 s = glm::scale(glm::mat4(1.0f), m_scale);

	return t * r * s;
}
