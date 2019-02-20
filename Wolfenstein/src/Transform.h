#pragma once

class Transform
{
public:
	Transform();

	void Rotate(float angle, const glm::vec3& axis);

	glm::mat4 CreateModelMatrix() const;

	inline glm::vec3 GetForward() const { return glm::vec3(0, 0, 1) * m_rot; }
	inline glm::vec3 GetUp() const { return glm::vec3(0, 1, 0) * m_rot; }
	inline glm::vec3 GetRight() const { return m_rot * glm::vec3(1, 0, 0); }

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::quat& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }
private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
};