#include "pch.h"
#include "Camera.h"

#include "Window.h"

Camera* Camera::s_instance;

Camera::Camera()
	: m_fov(0), m_zNear(0), m_zFar(0)
{
	if (s_instance == nullptr)
		s_instance = this;
}

void Camera::Init(float fov, float zNear, float zFar)
{
	m_fov = fov;
	m_zNear = zNear;
	m_zFar = zFar;
}

glm::mat4 Camera::CreateProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_fov), GetInstance(Window).GetAspect(), m_zNear, m_zFar);
}

glm::mat4 Camera::CreateViewMatrix()
{
	glm::mat4 t = glm::translate(glm::mat4(1.0f), -m_transform.GetPos());
	glm::mat4 r = glm::mat4_cast(GetTransform().GetRot());

	return r * t;
}