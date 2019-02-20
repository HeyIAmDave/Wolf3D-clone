#include "pch.h"
#include "Loader.h"

Loader* Loader::s_instance;

Loader::Loader()
{
	if (s_instance == nullptr)
		s_instance = this;
}

Shader & Loader::LoadShader(const std::string & filePath)
{
	return m_shaderLoader.Load("shaders/" + filePath);
}

Texture & Loader::LoadTexture(const std::string & filePath)
{
	return m_textureLoader.Load("textures/" + filePath);
}

Model & Loader::CreateModel(const std::string & name, const Mesh & mesh)
{
	return m_modelLoader.Create(name, mesh);
}

Sprite & Loader::CreateSprite(const std::string & name, unsigned int textureIndex, TextureAtlas & textureAtlas)
{
	return m_spriteLoader.Create(name, textureIndex, textureAtlas);
}

void Loader::CleanUp()
{
	m_shaderLoader.CleanUp();
	m_textureLoader.CleanUp();
	m_modelLoader.CleanUp();
	m_spriteLoader.CleanUp();
}