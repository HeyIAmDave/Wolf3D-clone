#pragma once

class AABB
{
public:
	AABB();

	void Init(const glm::vec3& pos, const glm::vec3 & halfExtents);

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetExtents() { return m_halfExtents; }
private:
	glm::vec3 m_pos;
	glm::vec3 m_halfExtents;
};