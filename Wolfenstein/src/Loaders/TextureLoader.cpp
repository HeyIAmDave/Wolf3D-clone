#include "pch.h"
#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureLoader::TextureLoader()
{ }

Texture & TextureLoader::Load(const std::string & fileName)
{
	if (m_list.find(fileName) == m_list.end())
	{
		int w, h;
		unsigned char* data = stbi_load(("./data/" + fileName).c_str(), &w, &h, 0, 4);
		if (data == NULL)
			printf("Error: failed to load texture: %s\n", fileName.c_str());

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();

		texture->Init(data, w, h);
		stbi_image_free(data);

		m_list[fileName] = texture;
	}

	return *m_list[fileName];
}