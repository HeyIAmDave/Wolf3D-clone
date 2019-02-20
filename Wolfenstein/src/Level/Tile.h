#pragma once
#include "TileTypes.h"

class Tile
{
public:
	Tile();

	void Init(const TileType& type, const glm::ivec3& color, const glm::ivec3& textures);

	unsigned int GetTextureIndex(unsigned int index) const;

	inline const TileType& GetType() const { return m_type; }
	inline glm::ivec3 GetColor() const { return m_color; }
private:
	TileType m_type;
	glm::ivec3 m_color;
	glm::ivec3 m_textures;
};