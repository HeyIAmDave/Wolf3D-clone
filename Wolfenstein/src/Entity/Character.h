#pragma once
#include "Transform.h"

class Character
{
public:
	Character() : m_speed(1.0f), m_velocity(0.0f) {}
	virtual ~Character() {}

	virtual void Init(float speed) {}
	virtual void Update(float delta) {}
	virtual void Render() {}
	virtual void CleanUp() {}

	inline Transform& GetTransform() { return m_transform; }
	inline glm::vec3& GetVelocity() { return m_velocity; }
	inline float& GetSpeed() { return m_speed; }
private:
	Transform m_transform;
	glm::vec3 m_velocity;
	float m_speed;
};