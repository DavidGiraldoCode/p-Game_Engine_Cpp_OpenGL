#include "Material.h"
#include "graphics/ShaderProgram.h"

namespace eng
{

	void Material::SetShaderProgram(ShaderProgram* shaderProgram)
	{
		delete m_shaderProgram;
		m_shaderProgram = shaderProgram;
		delete shaderProgram;
		shaderProgram = nullptr;
	}

	void Material::SetMaterialParameters(const string& paramName, float value)
	{
		m_parameters[paramName] = value;
	}

	void Material::Bind()
	{
		if (m_shaderProgram == nullptr)
			return;

		m_shaderProgram->Bind();
		for (const auto& iterator : m_parameters)
		{
			m_shaderProgram->SetUniformFloat(iterator.first, iterator.second);
		}
	}

	/*Material::~Material()
	{
		delete m_shaderProgram;
		m_shaderProgram = nullptr;
	}*/
}