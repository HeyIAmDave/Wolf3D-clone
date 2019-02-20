#include "pch.h"
#include "TextureAtlas.h"

TextureAtlas::TextureAtlas()
	: m_rows(0), m_columns(0), m_width(0), m_height(0), m_pixelOffsetX(0), m_pixelOffsetY(0)
{ }

void TextureAtlas::Init(unsigned int rows, unsigned int columns, unsigned int width, unsigned int height, unsigned int pixelOffsetX, unsigned int pixelOffsetY)
{
	m_rows = rows;
	m_columns = columns;
	m_width = width;
	m_height = height;
	m_pixelOffsetX = pixelOffsetX;
	m_pixelOffsetY = pixelOffsetY;
}

std::vector<glm::vec2> TextureAtlas::GetTexCoords(unsigned int index) const
{
	float sizeX = 1.0f / m_rows;
	float sizeY = 1.0f / m_columns;
	int x = (index % m_rows);
	int y = (index / m_rows);

	float offsetX = (1.0f / m_width) * m_pixelOffsetX;
	float offsetY = (1.0f / m_height) * m_pixelOffsetY;

	std::vector<glm::vec2> texCoords
	{
		glm::vec2(x * sizeX + offsetX,		 y * sizeY + offsetY),
		glm::vec2(x * sizeX + offsetX,		 y * sizeY + sizeY - offsetY),
		glm::vec2(x * sizeX + sizeX - offsetX, y * sizeY + sizeY - offsetY),
		glm::vec2(x * sizeX + sizeX - offsetX, y * sizeY + offsetY)
	};

	return texCoords;
}