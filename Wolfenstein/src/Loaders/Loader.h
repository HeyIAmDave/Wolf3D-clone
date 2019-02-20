#pragma once
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "ModelLoader.h"
#include "SpriteLoader.h"

class Loader
{
public:
	Loader();

	Shader& LoadShader(const std::string& filePath);
	Texture& LoadTexture(const std::string& filePath);
	Model& CreateModel(const std::string& name, const Mesh& mesh);
	Sprite& CreateSprite(const std::string& name, unsigned int textureIndex, TextureAtlas& textureAtlas);

	void CleanUp();

	inline static Loader& Get() { return *s_instance; }
private:
	static Loader* s_instance;

	ShaderLoader m_shaderLoader;
	TextureLoader m_textureLoader;
	ModelLoader m_modelLoader;
	SpriteLoader m_spriteLoader;
};