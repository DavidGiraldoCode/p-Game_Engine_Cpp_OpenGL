#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>

using std::string;

namespace eng
{
	class ShaderProgram; // Forward declaration

	/// <summary>
	/// 
	/// </summary>
	class GraphicsAPI
	{
	public:
		// Default contructor

		//original: std::shared_ptr<ShaderProgram> instead of ShaderProgram*
		ShaderProgram*	CreateShaderProgram(string& vertexSourceCode, string& fragmentSourceCode);
		void			BindShaderProgram(ShaderProgram& shaderProgram);

	private:
		bool			IsShaderCompilationSuccessful(const GLuint& shader) const;
		bool			IsProgramLinkingSuccessful(const GLuint& program) const;
	};
}