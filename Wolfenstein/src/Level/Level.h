#pragma once
#include "TextureAtlas.h"
#include "LevelRenderer.h"
#include "Tile.h"

class Level
{
	using LevelData = std::vector<std::shared_ptr<Tile>>;
public:
	Level();

	void Init(const std::string& name, unsigned int sizeX, unsigned int sizeZ, const TextureAtlas& textureAtlas);
	void Update(float delta);
	void Render();
	void CleanUp();

	Tile& GetTile(int x, int z);

	inline glm::vec3& GetSpawnPoint() { return m_spawnPoint; }
	inline LevelData& GetLevelData() { return m_levelData; }
private:
	bool m_initialized;
	unsigned int m_levelSizeX, m_levelSizeZ;
	TextureAtlas m_textureAtlas;
	glm::vec3 m_spawnPoint;

	LevelRenderer m_levelRenderer;

	LevelData m_levelData;

private:
	void FillLevelData(unsigned char* data);
};