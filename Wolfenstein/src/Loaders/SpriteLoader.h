#pragma once
#include "BaseLoader.h"
#include "Rendering/Sprite.h"

class SpriteLoader : public BaseLoader<Sprite>
{
public:
	SpriteLoader();

	virtual Sprite& Load(const std::string& fileName) override;
	Sprite& Create(const std::string & name, unsigned int textureIndex, TextureAtlas& textureAtlas);
};