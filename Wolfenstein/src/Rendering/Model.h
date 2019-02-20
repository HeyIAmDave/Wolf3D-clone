#pragma once
#include "Mesh.h"

class Model
{
public:
	Model();

	void Init(const Mesh& mesh);
	void Render();
	void CleanUp();

private:
	enum Buffer
	{
		VERTEX_BUFFER,
		INDEX_BUFFER,

		NUM_BUFFERS
	};

private:
	unsigned int m_vao, m_indexCount, m_attribCount;
	unsigned int m_buffers[NUM_BUFFERS];
	bool m_initialized;

private:
	void AddAttribute(unsigned int size, unsigned int type, size_t stride, const void* pointer, bool normalize = false);
};