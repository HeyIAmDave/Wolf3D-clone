#include "pch.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window* Window::s_instance;
bool Window::IsCloseRequested = false;

Window::Window()
{
	if (s_instance == nullptr)
		s_instance = this;
}

static std::string GetSeverity(GLenum severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		return "Error(Severity high)";
	case GL_DEBUG_SEVERITY_MEDIUM:
		return "Error(Severity medium)";
	case GL_DEBUG_SEVERITY_LOW:
		return "Error(Severity low)";
	}

	return "Notification";
}

static void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
		fprintf(stderr, "%s: %s\n", GetSeverity(severity).c_str(), message);
}

void Window::Init(const std::string& title, unsigned int width, unsigned int height)
{
	m_ptr.title = title;
	m_ptr.width = width;
	m_ptr.height = height;

	glfwInit();
	glfwSetErrorCallback(GLFWErrorCallback);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(m_ptr.width, m_ptr.height, m_ptr.title.c_str(), 0, 0);
	glfwSetWindowUserPointer(m_window, &m_ptr);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		printf("Debuging enabled\n");
	}


	glClearColor(0, 0, 0, 1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
	{
		IsCloseRequested = true;
	});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
	{
		WindowPointer& ptr = *(WindowPointer*)glfwGetWindowUserPointer(window);
		ptr.width = width;
		ptr.height = height;
	});
}

void Window::Clear(unsigned int mask)
{
	glClear(mask);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::CleanUp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::GLFWErrorCallback(int error, const char * desc)
{
	printf("GLFW Error(%i): %s\n", error, desc);
}