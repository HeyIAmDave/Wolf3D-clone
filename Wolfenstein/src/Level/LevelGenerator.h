#pragma once
#include "Tile.h"
#include "TextureAtlas.h"
#include "Level/Level.h"

class LevelGenerator
{
public:
	LevelGenerator();

	void GenerateLevel(Level& level, unsigned int sizeX, unsigned int sizeZ, const TextureAtlas& textureAtlas, Mesh* mesh);
private:
	unsigned int m_sizeX, m_sizeZ;
	TextureAtlas m_textureAtlas;
	Level* m_level;

private:
	Tile& GetTile(int x, int z);

	void CreateRoof(const glm::vec3& pos, const Tile& tile, Mesh* mesh);
	void CreateFloor(const glm::vec3& pos, const Tile& tile, Mesh* mesh);
	void CreateWall(const glm::vec3& pos, int side, const Tile& tile, Mesh* mesh);
	Tile& GetNeigborNormalTile(int x, int z);

	bool CanCreateWall(int x, int z);

	void AddIndices(Mesh* mesh);
};