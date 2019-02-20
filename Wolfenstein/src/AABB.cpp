#include "pch.h"
#include "AABB.h"

AABB::AABB()
	: m_pos(0), m_halfExtents(0.5f)
{ }

void AABB::Init(const glm::vec3 & pos, const glm::vec3 & halfExtents)
{
	m_pos = pos;
	m_halfExtents = halfExtents;
}