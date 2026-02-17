#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

namespace eng
{
	class ShaderProgram
	{
	public: 
		
		explicit ShaderProgram(GLuint programId);
		// Disable default and copy constructor
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;

		~ShaderProgram();

		ShaderProgram& operator = (const ShaderProgram&) = delete;
		
		void Bind() const;
		void SetUniformFloat(const string& uniformName, float value);
		
		const GLint GetUniformLocation(const string& uniformName);

	private:
		GLuint							m_shaderProgramId		= 0;
		unordered_map<string, GLint>	m_uniformLocationCache	= {};
	};
}