#pragma once
#include "Window.h"
#include "SceneManager.h"

class Application
{
public:
	Application();

	void Init();

	inline static Application& Get() { return *s_instance; }
	inline bool IsRunning() const { return m_isRunning; }
	inline Window GetWindow() const { return m_window; }
protected:
	static Application* s_instance;
	Window m_window;
	SceneManager m_sceneManager;
	Loader m_loader;
	bool m_isRunning;

private:
	void OnUpdate();
	void OnRender();
	void Close();
	void CleanUp();

};