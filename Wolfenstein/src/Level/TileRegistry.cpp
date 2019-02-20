#include "pch.h"
#include "TileRegistry.h"

TileRegistry* TileRegistry::s_instance;

TileRegistry::TileRegistry()
{
	if (s_instance == nullptr)
		s_instance = this;
}

void TileRegistry::Init()
{
	AddTile(TILE_EMPTY, { 0, 0, 0 }, { 0, 0, 0 }); // Empty
	AddTile(TILE_PLAYER_SPAWN, { 0, 255, 0 }, { 0, 0, 0 }); // Player spawn
	AddTile(TILE_NORMAL, { 255, 255, 0 }, { 42, 83, 0 }); // Stone walls
	AddTile(TILE_NORMAL, { 255, 255, 1 }, { 42, 83, 10 }); // Stone walls statue
	AddTile(TILE_NORMAL, { 255, 255, 2 }, { 42, 83, 22 }); // Wood walls
	AddTile(TILE_NORMAL, { 255, 255, 3 }, { 42, 83, 18 }); // Wood walls painting
	AddTile(TILE_DOOR, { 255, 0, 0 }, { 28, 28, 100 }); // Door
}

void TileRegistry::CleanUp()
{
	m_tiles.clear();
}

Tile & TileRegistry::GetTile(const glm::ivec3 & tileColor)
{
	for (auto& t : m_tiles)
		if (t->GetColor() == tileColor)
			return *t;

	return *m_tiles[0];
}

Tile& TileRegistry::GetTile(const TileType& type)
{
	for (auto& t : m_tiles)
		if (t->GetType() == type)
			return *t;

	return *m_tiles[0];
}

void TileRegistry::AddTile(const TileType& type, const glm::ivec3& color, const glm::ivec3& textures)
{
	std::shared_ptr<Tile> tile = std::make_shared<Tile>();
	tile->Init(type, color, textures);
	m_tiles.push_back(tile);
}