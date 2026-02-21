#pragma once
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

namespace eng
{
	class ShaderProgram;

	class Material
	{
	public:
		//Material() = delete;
		~Material();
		// original parameter: const std::shared_ptr<ShaderProgram>& shaderProgram
		void SetShaderProgram(ShaderProgram* shaderProgram);
		void SetMaterialParameters(const string& paramName, float value);
		void Bind();

	private:
		// original std::shared_ptr<ShaderProgram>
		ShaderProgram*					m_shaderProgram		= nullptr;
		unordered_map<string, float>	m_parameters		= {};
	};
}