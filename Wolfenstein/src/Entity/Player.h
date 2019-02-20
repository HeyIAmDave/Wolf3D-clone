#pragma once
#include "Camera.h"
#include "AABB.h"
#include "Character.h"

class Level;

class Player : public Character
{
public:
	Player();
	
	void Init(float speed, float lookSensitivity, Level& level, Camera& camera);
	virtual void Update(float delta) override;

private:
	Level* m_level;
	Camera* m_camera;
	float m_lookSensitivity;
	bool m_mouseLocked;
	AABB m_aabb;

	void CheckCollisions(const glm::vec3& velDir);

	void Move(float delta);
	void Look(float delta);
};