#pragma once

struct GLFWwindow;

class Window
{
public:
	Window();

	void Init(const std::string& title, unsigned int width, unsigned int height);

	void Clear(unsigned int mask = 0x00004000 | 0x00000100);
	void Update();

	void CleanUp();

	inline int GetWidth() const { return m_ptr.width; }
	inline int GetHeight() const { return m_ptr.height; }
	inline float GetAspect() const { return (float)m_ptr.width / m_ptr.height; }

	inline GLFWwindow* GetWindow() const { return m_window; }

	inline static Window& Get() { return *s_instance; }

	static bool IsCloseRequested;
private:
	struct WindowPointer
	{
		std::string title;
		unsigned int width, height;
	};

	static void GLFWErrorCallback(int error, const char* desc);
	// static void OGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

private:
	static Window* s_instance;
	WindowPointer m_ptr;
	GLFWwindow* m_window;
};