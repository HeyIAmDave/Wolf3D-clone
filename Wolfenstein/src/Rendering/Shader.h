#pragma once

class Shader
{
public:
	Shader();

	void Init(const std::string& vsrc, const std::string& fsrc);

	void Bind() const;
	void Unbind() const;

	void CleanUp();

public:
	void LoadUniform(const std::string&, int value);
	void LoadUniform(const std::string&, const glm::mat4& value);

private:
	unsigned int m_programID;
	bool m_initialized;

private:
	unsigned int CreateShader(unsigned int type, const std::string& src);
};