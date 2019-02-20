#pragma once

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;

	Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	{
		this->position = position;
		this->texCoord = texCoord;
	}
};