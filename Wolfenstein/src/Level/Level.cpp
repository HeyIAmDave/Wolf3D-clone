#include "pch.h"
#include "Level.h"
#include "TileRegistry.h"
#include "LevelGenerator.h"

#include <stb_image.h>

Level::Level()
	: m_initialized(false), m_levelSizeX(0), m_levelSizeZ(0)
{ }

void Level::Init(const std::string & name, unsigned int sizeX, unsigned int sizeZ, const TextureAtlas & textureAtlas)
{
	if (m_initialized)
		return;

	int w, h;
	unsigned char* data = stbi_load(("./data/levels/" + name + ".png").c_str(), &w, &h, 0, 3);
	if (data == NULL)
		printf("Error: failed to load level: %s\n", name.c_str());

	m_levelSizeX = w;
	m_levelSizeZ = h;
	m_textureAtlas = textureAtlas;

	FillLevelData(data);
	stbi_image_free(data);

	Mesh mesh;
	LevelGenerator gen;
	gen.GenerateLevel(*this, m_levelSizeX, m_levelSizeZ, m_textureAtlas, &mesh);

	m_levelRenderer.Init(name, mesh);

	m_initialized = true;
}

void Level::Update(float delta)
{
	if (!m_initialized)
		return;
}

#include <glad/glad.h>

void Level::Render()
{
	if (!m_initialized)
		return;

	m_levelRenderer.Render();
}

void Level::CleanUp()
{
	m_initialized = false;
	m_levelRenderer.CleanUp();
}

Tile & Level::GetTile(int x, int z)
{
	if (x >= m_levelSizeX || x < 0)
		return GetInstance(TileRegistry).GetTile(TILE_EMPTY);
	if (z >= m_levelSizeZ || z < 0)
		return GetInstance(TileRegistry).GetTile(TILE_EMPTY);

	return *m_levelData[x * m_levelSizeZ + z];
}

void Level::FillLevelData(unsigned char * data)
{
	for (unsigned int x = 0; x < m_levelSizeX; x++)
	{
		for (unsigned int z = 0; z < m_levelSizeZ; z++)
		{

			int index = (x * m_levelSizeZ + z) * 3;
			int r = data[index + 0];
			int g = data[index + 1];
			int b = data[index + 2];

			Tile& tile = GetInstance(TileRegistry).GetTile({ r, g, b });
			m_levelData.push_back(std::make_shared<Tile>(std::move(tile)));
		}
	}
}