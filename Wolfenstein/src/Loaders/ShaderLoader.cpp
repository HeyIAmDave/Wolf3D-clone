#include "pch.h"
#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{
}

Shader & ShaderLoader::Load(const std::string & fileName)
{
	if (m_list.find(fileName) == m_list.end())
	{
		ShaderSource src = LoadShaderFile(fileName);
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Init(src.vertexShader, src.fragmentShader);

		m_list[fileName] = shader;
	}

	return *m_list[fileName];
}

ShaderSource ShaderLoader::LoadShaderFile(const std::string & filePath)
{
	ShaderSource result;
	std::ifstream file("./data/" + filePath);
	if (!file.good())
	{
		printf("Failed to Load shader file: %s\n", filePath.c_str());
		return result;
	}

	std::string line;
	std::string currentShader = "";

	while (std::getline(file, line))
	{
		if (line == "#vertexShader" || line == "#fragmentShader")
		{
			currentShader = line;
			continue;
		}

		if (currentShader == "#vertexShader")
			result.vertexShader += line + "\n";
		else
			result.fragmentShader += line + "\n";
	}

	file.close();
	return result;
}