#pragma once
#include "TextureAtlas.h"

class Sprite
{
public:
	Sprite();

	void Init(unsigned int textureIndex, TextureAtlas& textureAtlas);
	void UpdateTexCoords(unsigned int textureIndex);
	void Render();
	void CleanUp();
private:
	enum Buffers
	{
		POSITION_BUFFER,
		TEXCOORD_BUFFER,
		INDEX_BUFFER,

		NUM_BUFFERS
	};

private:
	unsigned int m_vao;
	unsigned int m_buffers[NUM_BUFFERS];
	bool m_initialized;
	TextureAtlas m_textureAtlas;
};