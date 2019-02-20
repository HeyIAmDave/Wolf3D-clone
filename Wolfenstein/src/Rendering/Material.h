#pragma once

class Material
{
public:
	void Init(const std::string& shaderName, const std::string& textureName);
	void Init(const Shader& shader, const Texture& texture);

	void Bind();
	void Unbind() const;

	inline Shader& GetShader() { return m_shader; }
	inline Texture& GetTexture() { return m_texture; }
private:
	Shader m_shader;
	Texture m_texture;
};