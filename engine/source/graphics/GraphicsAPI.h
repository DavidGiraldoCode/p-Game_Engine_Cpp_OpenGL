#pragma once
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

		ShaderProgram*	CreateShaderProgram(string& vertexShaderSource, string& fragmentShaderSource);
		void			BindShaderProgram(ShaderProgram& shaderProgram);
	};
}