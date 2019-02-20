#include "pch.h"
#include "Sprite.h"

#include <glad/glad.h>

Sprite::Sprite()
	: m_vao(0), m_initialized(false)
{ }

void Sprite::Init(unsigned int textureIndex, TextureAtlas& textureAtlas)
{
	if (m_initialized)
		return;

	m_textureAtlas = textureAtlas;

	std::vector<glm::vec2> vertices
	{
		{ 0.5f, 1.0f },
		{ 0.5f, 0.0f },
		{ -0.5f, 0.0f },
		{ -0.5f, 1.0f },
	};

	std::vector<glm::vec2> texCoord = m_textureAtlas.GetTexCoords(textureIndex);

	std::vector<uint8_t> indices
	{
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(NUM_BUFFERS, m_buffers);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[POSITION_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEXCOORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoord.size(), texCoord.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	m_initialized = true;
}

void Sprite::UpdateTexCoords(unsigned int textureIndex)
{
	if (!m_initialized)
		return;

	std::vector<glm::vec2> texCoord = m_textureAtlas.GetTexCoords(textureIndex);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEXCOORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoord.size(), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * texCoord.size(), texCoord.data());
}

void Sprite::Render()
{
	if (!m_initialized)
		return;

	glDisable(GL_CULL_FACE);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEX_BUFFER]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	glEnable(GL_CULL_FACE);
}

void Sprite::CleanUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, m_buffers);

	m_initialized = false;
}