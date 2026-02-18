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
		/// <summary>
		/// This is an explicit constructor that does not allow for implicit cast from GLuint to ShaderProgram.
		/// Therefore, only by explicitly creating a GLuint handler a ShaderProgram instance can be instantiated.
		/// </summary>
		explicit ShaderProgram(GLuint programId);

		// Disable default means that the a user will not be able to create a ShaderProgram by just declaring an instance.
		// Calling `ShaderPragram sp; will yield an error. And assinging to an `int` will not work. This ensures the program id
		// comes from a valid OpenGL action on the GPU.
		ShaderProgram() = delete;
		
		// and copy constructor
		ShaderProgram(const ShaderProgram&) = delete;

		~ShaderProgram();

		ShaderProgram& operator = (const ShaderProgram&) = delete;
		
		void Bind() const;
		void SetUniformFloat(const string& uniformName, float value);
		
		/// <summary>
		/// Checks if the uniform name is stored in cache, otherwise, adds it, and returns the location
		/// </summary>
		GLint GetUniformLocation(const string& uniformName);

	private:
		GLuint							m_shaderProgramId		= 0;
		unordered_map<string, GLint>	m_uniformLocationCache	= {};
	};
}