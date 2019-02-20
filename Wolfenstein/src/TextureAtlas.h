#pragma once

class TextureAtlas
{
public:
	TextureAtlas();
	void Init(unsigned int rows, unsigned int columns, unsigned int width, unsigned int height, unsigned int pixelOffsetX, unsigned int pixelOffsetY);

	std::vector<glm::vec2> GetTexCoords(unsigned int index) const;

private:
	unsigned int m_rows, m_columns, m_width, m_height, m_pixelOffsetX, m_pixelOffsetY;
};