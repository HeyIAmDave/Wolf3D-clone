#include "pch.h"
#include "Texture.h"

#include <glad/glad.h>

Texture::Texture()
	: m_textureID(0), m_initialized(false)
{ }

void Texture::Init(unsigned char * data, int w, int h, unsigned int internalFormat, unsigned int format)
{
	if (m_initialized)
		return;

	m_width = (unsigned int)w;
	m_height = (unsigned int)h;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

	m_initialized = true;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::CleanUp()
{
	glDeleteTextures(1, &m_textureID);
	m_initialized = false;
}