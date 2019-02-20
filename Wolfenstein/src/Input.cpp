#include "pch.h"
#include "Input.h"
#include "Window.h"

#include <GLFW/glfw3.h>

Input* Input::s_instance = new Input();

void Input::LockCursor(bool value)
{
	auto window = GetInstance(Window).GetWindow();
	if (value == true)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Input::GetKey(int keyCode)
{
	auto window = GetInstance(Window).GetWindow();
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

bool Input::GetKeyDown(int keyCode)
{
	auto window = GetInstance(Window).GetWindow();

	static int prevState[512];
	// prevState[keyCode] = GLFW_RELEASE;
	int curState = glfwGetKey(window, keyCode);

	if (curState == GLFW_PRESS && prevState[keyCode] == GLFW_RELEASE)
	{
		prevState[keyCode] = GLFW_PRESS;
		return true;
	}

	prevState[keyCode] = curState;
	return false;
}

bool Input::GetKeyUp(int keyCode)
{
	auto window = GetInstance(Window).GetWindow();
	return glfwGetKey(window, keyCode) == GLFW_RELEASE;
}

bool Input::GetMouseButton(int button)
{
	auto window = GetInstance(Window).GetWindow();
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool Input::GetMouseButtonDown(int button)
{
	auto window = GetInstance(Window).GetWindow();

	static int prevState[256];
	int curState = glfwGetMouseButton(window, button);

	if (curState == GLFW_PRESS && prevState[button] == GLFW_RELEASE)
	{
		prevState[button] = curState;
		return true;
	}
	prevState[button] = curState;
	return false;
}

bool Input::GetMouseButtonUp(int button)
{
	auto window = GetInstance(Window).GetWindow();
	return glfwGetMouseButton(window, button) == GLFW_RELEASE;
}

glm::vec2 Input::GetMousePosition() const
{
	auto window = GetInstance(Window).GetWindow();
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return { (float)x, (float)y };
}
