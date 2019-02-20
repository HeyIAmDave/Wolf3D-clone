#pragma once
#include "Tile.h"

class TileRegistry
{
public:
	TileRegistry();

	void Init();
	void CleanUp();

	inline static TileRegistry& Get() { return *s_instance; }

	Tile& GetTile(const glm::ivec3& tileColor);
	Tile& GetTile(const TileType& type);
private:
	static TileRegistry* s_instance;
	std::vector<std::shared_ptr<Tile>> m_tiles;

private:
	void AddTile(const TileType& type, const glm::ivec3& color, const glm::ivec3& textures);
};