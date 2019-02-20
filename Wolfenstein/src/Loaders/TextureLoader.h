#pragma once
#include "BaseLoader.h"
#include "Rendering/Texture.h"

class TextureLoader : public BaseLoader<Texture>
{
public:
	TextureLoader();

	virtual Texture& Load(const std::string& fileName) override;
};