#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>

using std::string;

namespace eng
{
	// Forward declaration for pointers
	class ShaderProgram; 
	class Material;
	class Mesh;

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
		void			BindMesh(Mesh& mesh);
		//////////////////////////////////////////////////////////////////////
		// Buffer creation
		//////////////////////////////////////////////////////////////////////
		GLuint			CreateVertexBuffer(const float* vertices, const size_t verticesCount);
		GLuint			CreateIndexBuffer(const uint32_t* indices, const size_t indicesCount);
		
		void			SetClearColor(const float r, const float g, const float b, const float a);
		void			ClearBuffers();
		void			DrawMesh(Mesh& mesh);

	private:
		bool			IsShaderCompilationSuccessful(const GLuint shader) const;
		bool			IsProgramLinkingSuccessful(const GLuint program) const;
	};
}