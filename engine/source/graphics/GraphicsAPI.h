#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>

using std::string;

namespace eng
{
	// Forward declaration
	class ShaderProgram; 
	class Material;

	/// <summary>
	/// 
	/// </summary>
	class GraphicsAPI
	{
	public:
		// Default contructor is not deleted, so anyone can create a GraphicsAPI instance,
		// unlike the InputManager that uses friend class Engine to call its private constructor
		
		/// <summary>
		/// Creates a ShaderProgram pointer on the heap. The caller must manage this resource manually
		/// original: std::shared_ptr<ShaderProgram> instead of ShaderProgram*
		/// </summary>
		ShaderProgram*	CreateShaderProgram(const string& vertexSourceCode, const string& fragmentSourceCode);
		void			BindShaderProgram(ShaderProgram& shaderProgram); // original ShaderProgram*
		void			BindMaterial(Material& material); //original Material* 

	private:
		bool			IsShaderCompilationSuccessful(const GLuint shader) const;
		bool			IsProgramLinkingSuccessful(const GLuint program) const;
	};
}