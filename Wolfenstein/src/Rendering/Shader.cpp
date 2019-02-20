#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>

Shader::Shader()
	: m_programID(0), m_initialized(false)
{ }

void Shader::Init(const std::string & vsrc, const std::string & fsrc)
{
	if (m_initialized)
		return;

	unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vsrc);
	unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsrc);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);

	glLinkProgram(m_programID);

	int result = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLsizei length = 0;
		GLchar msg[1024];
		glGetProgramInfoLog(m_programID, 1024, &length, msg);

		printf("Error: %s\n", msg);
	}

	glDetachShader(m_programID, vertexShader);
	glDetachShader(m_programID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_initialized = true;
}

void Shader::Bind() const
{
	glUseProgram(m_programID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::CleanUp()
{
	glDeleteProgram(m_programID);
	m_initialized = false;
}

void Shader::LoadUniform(const std::string & name, int value)
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::LoadUniform(const std::string & name, const glm::mat4 & value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

unsigned int Shader::CreateShader(unsigned int type, const std::string & src)
{
	unsigned int id = glCreateShader(type);
	const char* code = src.c_str();
	const int codeLength = src.size();

	glShaderSource(id, 1, &code, &codeLength);
	glCompileShader(id);

	int result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLsizei length = 0;
		GLchar msg[1024];
		glGetShaderInfoLog(id, 1024, &length, msg);

		printf("Error: %s\n", msg);
	}

	return id;
}
