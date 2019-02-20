#include "pch.h"
#include "SceneManager.h"

SceneManager* SceneManager::s_instance;

SceneManager::SceneManager()
	: m_scene(0)
{
	if (s_instance == nullptr)
		s_instance = this;
}

SceneManager::~SceneManager()
{ }

void SceneManager::LoadScene(Scene * scene)
{
	if (m_scene != nullptr)
		UnloadScene();

	m_scene = scene;
	m_scene->OnLoadContent();
}

void SceneManager::UnloadScene()
{
	if (m_scene == nullptr)
		return;

	m_scene->OnUnloadContent();

	delete m_scene;
	m_scene = 0;
}

void SceneManager::OnUpdate(float delta)
{
	if (m_scene == nullptr)
		return;

	m_scene->OnUpdate(delta);
}

void SceneManager::OnRender()
{
	if (m_scene == nullptr)
		return;

	m_scene->OnRender();
}