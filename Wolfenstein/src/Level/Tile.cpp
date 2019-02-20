#include "pch.h"
#include "Tile.h"

Tile::Tile()
	: m_type(TILE_EMPTY), m_color(0), m_textures(0)
{ }

void Tile::Init(const TileType& type, const glm::ivec3& color, const glm::ivec3& textures)
{
	m_type = type;
	m_color = color;
	m_textures = textures;
}

unsigned int Tile::GetTextureIndex(unsigned int index) const
{
	// 0 = Roof, 1 = Floor, 2 = Walls
	switch (index)
	{
		case 0: return m_textures.r;
		case 1: return m_textures.g;
		case 2: return m_textures.b;
	}

	return 0;
}