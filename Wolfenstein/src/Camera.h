#pragma once
#include "Transform.h"

class Camera
{
public:
	Camera();

	void Init(float fov, float zNear = 0.01f, float zFar = 1000.0f);

	inline Transform& GetTransform() { return m_transform; }

	glm::mat4 CreateProjectionMatrix() const;
	glm::mat4 CreateViewMatrix();

	inline static Camera& Get() { return *s_instance; }
private:
	static Camera* s_instance;

	Transform m_transform;
	float m_fov, m_zNear, m_zFar;
};