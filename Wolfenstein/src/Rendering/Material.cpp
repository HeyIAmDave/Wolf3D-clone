#include "pch.h"
#include "Material.h"

#include "Camera.h"

void Material::Init(const std::string & shaderName, const std::string & textureName)
{
	Init(GetInstance(Loader).LoadShader(shaderName), GetInstance(Loader).LoadTexture(textureName));
}

void Material::Init(const Shader & shader, const Texture & texture)
{
	m_shader = shader;
	m_texture = texture;
}

void Material::Bind()
{
	m_texture.Bind();
	m_shader.Bind();
	m_shader.LoadUniform("_proj", GetInstance(Camera).CreateProjectionMatrix());
	m_shader.LoadUniform("_view", GetInstance(Camera).CreateViewMatrix());
}

void Material::Unbind() const
{
	m_shader.Unbind();
	m_texture.Unbind();
}
