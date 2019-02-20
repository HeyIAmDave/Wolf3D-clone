#include "pch.h"
#include "TestScene.h"

#include "Window.h"

#include <glad/glad.h>

TestScene::TestScene()
{ }

TestScene::~TestScene()
{ }

void TestScene::OnLoadContent()
{
	m_tileRegistry.Init();

	m_camera.Init(110.0f);

	auto& atlasTexture = GetInstance(Loader).LoadTexture("wolfenstein_atlas.png");
	m_mainAtlas.Init(16, 43, atlasTexture.GetWidth(), atlasTexture.GetHeight(), 1, 1);

	m_level.Init("testLevel", 0, 0, m_mainAtlas);
	// m_level.Init("testOpenLevel", 0, 0, m_mainAtlas);

	m_player.Init(4.0f, 250.0f, m_level, m_camera);
	m_transform.GetPos() = m_player.GetTransform().GetPos();

	m_material.Init("spriteShader.glsl", "wolfenstein_atlas.png");
	m_soldier.Init(1.0f, m_player, m_level, m_mainAtlas);
	m_soldier.GetTransform().GetPos() = m_player.GetTransform().GetPos() + glm::vec3(0, 0, 5);

	contentLoaded = true;
}

void TestScene::OnUnloadContent()
{
	m_tileRegistry.CleanUp();
	contentLoaded = false;
}

void TestScene::OnUpdate(float delta)
{
	if (!contentLoaded)
		return;

	m_level.Update(delta);
	m_player.Update(delta);
	m_soldier.Update(delta);
}

void TestScene::OnRender()
{
	if (!contentLoaded)
		return;

	static bool wireframe = false;
	if (Input::IsKeyDown(KEY_F1))
	{
		glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
		wireframe = !wireframe;
	}

	m_level.Render();

	m_material.Bind();
	m_material.GetShader().LoadUniform("_model", m_soldier.GetTransform().CreateModelMatrix());
	m_soldier.Render();
	m_material.Unbind();
}