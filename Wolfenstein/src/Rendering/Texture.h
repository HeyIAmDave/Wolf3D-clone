#pragma once

class Texture
{
public:
	Texture();

	void Init(unsigned char* data, int w, int h, unsigned int internalFormat = 0x1908, unsigned int format = 0x1908);
	
	void Bind() const;
	void Unbind() const;

	void CleanUp();

	inline unsigned int GetID() const { return m_textureID; }
	inline unsigned int GetWidth() const { return m_width; }
	inline unsigned int GetHeight() const { return m_height; }
private:
	unsigned int m_textureID, m_width, m_height;
	bool m_initialized;
};