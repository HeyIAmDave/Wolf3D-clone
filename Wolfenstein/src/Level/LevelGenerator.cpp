#include "pch.h"
#include "LevelGenerator.h"
#include "TileRegistry.h"

LevelGenerator::LevelGenerator()
	: m_sizeX(0), m_sizeZ(0)
{ }

void LevelGenerator::GenerateLevel(Level& level, unsigned int sizeX, unsigned int sizeZ, const TextureAtlas& textureAtlas, Mesh * mesh)
{
	m_sizeX = sizeX;
	m_sizeZ = sizeZ;
	m_textureAtlas = textureAtlas;
	m_level = &level;

	for (unsigned int x = 0; x < m_sizeX; x++)
	{
		for (unsigned int z = 0; z < m_sizeZ; z++)
		{
			Tile tile = GetTile(x, z);
			if (tile.GetType() == TILE_EMPTY)
				continue;

			if (tile.GetType() == TILE_PLAYER_SPAWN)
			{
				m_level->GetSpawnPoint() = { x, 0, z };
				tile = GetNeigborNormalTile(x, z);
			}

			// North
			if (CanCreateWall(x, z + 1))
				CreateWall({ x, 0, z }, 0, tile, mesh);
			// East
			if (CanCreateWall(x - 1, z))
				CreateWall({ x, 0, z }, 1, tile, mesh);
			// South
			if (CanCreateWall(x, z - 1))
				CreateWall({ x, 0, z }, 2, tile, mesh);
			// West
			if (CanCreateWall(x + 1, z))
				CreateWall({ x, 0, z }, 3, tile, mesh);


			if (tile.GetType() == TILE_DOOR)
				tile = GetNeigborNormalTile(x, z);

			CreateFloor({ x, 0, z }, tile, mesh);
			CreateRoof({ x, 0, z }, tile, mesh);
		}
	}
}

Tile& LevelGenerator::GetTile(int x, int z)
{
	return *m_level->GetLevelData()[x * m_sizeZ + z];
}

void LevelGenerator::CreateRoof(const glm::vec3 & pos, const Tile & tile, Mesh * mesh)
{
	auto& texCoord = m_textureAtlas.GetTexCoords(tile.GetTextureIndex(0));

	mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z }, texCoord[0]));
	mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f }, texCoord[1]));
	mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z + 1.0f }, texCoord[2]));
	mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z }, texCoord[3]));

	AddIndices(mesh);
}

void LevelGenerator::CreateFloor(const glm::vec3 & pos, const Tile & tile, Mesh * mesh)
{
	auto& texCoord = m_textureAtlas.GetTexCoords(tile.GetTextureIndex(1));

	mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z }, texCoord[0]));
	mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z + 1.0f}, texCoord[1]));
	mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z + 1.0f }, texCoord[2]));
	mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z }, texCoord[3]));

	AddIndices(mesh);
}

void LevelGenerator::CreateWall(const glm::vec3 & pos, int side, const Tile & tile, Mesh * mesh)
{
	auto& texCoord = m_textureAtlas.GetTexCoords(tile.GetTextureIndex(2));

	// 0 = North, 1 = East, 2 = South, 3 = West
	switch (side)
	{
	case 0:
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f }, texCoord[0])); // 1
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z + 1.0f }, texCoord[1])); // 2
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z + 1.0f }, texCoord[2])); // 3
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z + 1.0f }, texCoord[3])); // 4

		AddIndices(mesh);
		return;

	case 1:
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z + 1.0f }, texCoord[0]));
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z + 1.0f }, texCoord[1]));
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z }, texCoord[2]));
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z }, texCoord[3]));

		AddIndices(mesh);
		return;

	case 2:
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y + 1.0f, pos.z }, texCoord[0]));
		mesh->vertices.emplace_back(Vertex({ pos.x, pos.y, pos.z }, texCoord[1]));
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z }, texCoord[2]));
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z }, texCoord[3]));


		AddIndices(mesh);
		return;

	case 3:
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z }, texCoord[0]));
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z }, texCoord[1]));
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y, pos.z + 1.0f }, texCoord[2]));
		mesh->vertices.emplace_back(Vertex({ pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f }, texCoord[3]));


		AddIndices(mesh);
		return;
	}
}

Tile & LevelGenerator::GetNeigborNormalTile(int x, int z)
{
	Tile tile = GetTile(x, z + 1);
	if (tile.GetType() == TILE_NORMAL)
		return tile;

	tile = GetTile(x, z - 1);
	if (tile.GetType() == TILE_NORMAL)
		return tile;

	tile = GetTile(x + 1, z);
	if (tile.GetType() == TILE_NORMAL)
		return tile;

	tile = GetTile(x - 1, z);
	if (tile.GetType() == TILE_NORMAL)
		return tile;

	return GetInstance(TileRegistry).GetTile(TILE_EMPTY);
}

bool LevelGenerator::CanCreateWall(int x, int z)
{
	auto& tile = GetTile(x, z);
	return tile.GetType() == TILE_EMPTY;
}

void LevelGenerator::AddIndices(Mesh * mesh)
{
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 4);
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 3);
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 2);
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 4);
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 2);
	mesh->indices.emplace_back((unsigned int)mesh->vertices.size() - 1);
}