#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void LoadScene(Scene* scene);
	void UnloadScene();

	void OnUpdate(float delta);
	void OnRender();

	inline static SceneManager& Get() { return *s_instance; }
private:
	static SceneManager* s_instance;
	Scene* m_scene;
};