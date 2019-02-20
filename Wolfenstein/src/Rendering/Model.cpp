#include "pch.h"
#include "Model.h"

#include <glad/glad.h>

Model::Model()
	: m_vao(0), m_indexCount(0), m_attribCount(0), m_initialized(false)
{ }

void Model::Init(const Mesh & mesh)
{
	if (m_initialized)
		return;

	m_indexCount = mesh.indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(NUM_BUFFERS, m_buffers);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

	AddAttribute(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	AddAttribute(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_initialized = true;
}

void Model::Render()
{
	if (!m_initialized)
		return;

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEX_BUFFER]);

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

void Model::CleanUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(NUM_BUFFERS, m_buffers);
	m_indexCount = 0;
	m_attribCount = 0;
	m_initialized = false;
}

void Model::AddAttribute(unsigned int size, unsigned int type, size_t stride, const void * pointer, bool normalize)
{
	glEnableVertexAttribArray(m_attribCount);
	glVertexAttribPointer(m_attribCount++, size, type, normalize, stride, pointer);
}