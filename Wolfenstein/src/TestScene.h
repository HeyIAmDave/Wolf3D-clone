#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Entity/Player.h"
#include "TextureAtlas.h"
#include "Level/Level.h"
#include "Level/TileRegistry.h"

#include "Entity/BlueSoldier.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void OnLoadContent() override;
	virtual void OnUnloadContent() override;
	virtual void OnUpdate(float delta) override;
	virtual void OnRender() override;
private:
	Camera m_camera;
	Player m_player;
	Transform m_transform;
	TextureAtlas m_mainAtlas;
	TileRegistry m_tileRegistry;
	Level m_level;

	Material m_material;
	BlueSoldier m_soldier;
};