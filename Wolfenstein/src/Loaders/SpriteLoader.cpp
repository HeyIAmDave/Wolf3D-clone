#include "pch.h"
#include "SpriteLoader.h"

SpriteLoader::SpriteLoader()
{ }

Sprite & SpriteLoader::Load(const std::string & fileName)
{
	return *m_list[fileName];
}

Sprite & SpriteLoader::Create(const std::string & name, unsigned int textureIndex, TextureAtlas & textureAtlas)
{
	if (m_list.find(name) == m_list.end())
	{
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
		sprite->Init(textureIndex, textureAtlas);
		m_list[name] = sprite;
	}

	return *m_list[name];
}