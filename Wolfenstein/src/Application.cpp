#include "pch.h"
#include "Application.h"
#include "TestScene.h"

#include <GLFW/glfw3.h>

Application* Application::s_instance;

Application::Application()
	: m_isRunning(false)
{
	if (s_instance == nullptr)
		s_instance = this;
}

void Application::Init()
{
	if (m_isRunning)
		return;

	m_window.Init("Wolfenstein Clone", 1920, 1080);

	m_sceneManager.LoadScene(new TestScene());

	m_isRunning = true;
	OnUpdate();
}

void Application::OnUpdate()
{
	float LAST_TIME = (float)glfwGetTime();

	while (m_isRunning)
	{
		float CURRENT_TIME = (float)glfwGetTime();
		float DELTA_TIME = CURRENT_TIME - LAST_TIME;
		LAST_TIME = CURRENT_TIME;

		if (Window::IsCloseRequested)
			Close();

		m_sceneManager.OnUpdate(DELTA_TIME);

		OnRender();
	}

	CleanUp();
}

void Application::OnRender()
{
	m_window.Clear();
	m_sceneManager.OnRender();
	m_window.Update();
}

void Application::Close()
{
	m_isRunning = false;
}

void Application::CleanUp()
{
	m_sceneManager.UnloadScene();
	m_loader.CleanUp();
	m_window.CleanUp();
}