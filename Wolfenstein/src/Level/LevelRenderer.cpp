#include "pch.h"
#include "LevelRenderer.h"

LevelRenderer::LevelRenderer()
	: m_initialized(false)
{ }

void LevelRenderer::Init(const std::string& name, const Mesh & mesh)
{
	if (m_initialized)
		return;

	m_model = GetInstance(Loader).CreateModel(name, mesh);
	m_material.Init("levelShader.glsl", "wolfenstein_atlas.png");

	m_initialized = true;
}

void LevelRenderer::Render()
{
	if (!m_initialized)
		return;

	m_material.Bind();
	m_model.Render();
	m_material.Unbind();
}

void LevelRenderer::CleanUp()
{
	m_initialized = false;
}