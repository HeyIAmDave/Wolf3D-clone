#pragma once
#include <KeyCodes.h>

class Input
{
public:
	inline static bool IsKeyPressed(int keyCode) { return s_instance->GetKey(keyCode); }
	inline static bool IsKeyDown(int keyCode) { return s_instance->GetKeyDown(keyCode); }
	inline static bool IsKeyUp(int keyCode) { return s_instance->GetKeyUp(keyCode); }

	inline static bool IsMouseButtonPressed(int button) { return s_instance->GetMouseButton(button); }
	inline static bool IsMouseButtonDown(int button) { return s_instance->GetMouseButtonDown(button); }
	inline static bool IsMouseButtonUp(int button) { return s_instance->GetMouseButtonUp(button); }
	inline static glm::vec2 GetMousePos() { return s_instance->GetMousePosition(); }

	static void LockCursor(bool value);

private:
	static Input* s_instance;

	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	bool GetMouseButton(int button);
	bool GetMouseButtonDown(int button);
	bool GetMouseButtonUp(int button);

	glm::vec2 GetMousePosition() const;
};