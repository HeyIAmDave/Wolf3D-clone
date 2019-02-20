#pragma once
#include "BaseLoader.h"
#include "Rendering/Shader.h"

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class ShaderLoader : public BaseLoader<Shader>
{
public:
	ShaderLoader();

	virtual Shader& Load(const std::string& fileName) override;

private:
	ShaderSource LoadShaderFile(const std::string& filePath);
};