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
		/// original return type: std::shared_ptr<ShaderProgram>
		/// </summary>
		ShaderProgram*	CreateShaderProgram(const string& vertexSourceCode, const string& fragmentSourceCode);
		

		//////////////////////////////////////////////////////////////////////
		// Buffer creation
		//////////////////////////////////////////////////////////////////////

		// Original parameter: const std::vector<float>& vertices
		GLuint			CreateVertexBuffer(const float* vertices, const size_t verticesCount);
		// Original parameter: const std::vector<uint32_t>& indices
		GLuint			CreateIndexBuffer(const uint32_t* indices, const size_t indicesCount);
		
		//////////////////////////////////////////////////////////////////////
		// Buffer binding
		//////////////////////////////////////////////////////////////////////
		void			BindShaderProgram(ShaderProgram* shaderProgram); // original parameter type: ShaderProgram*
		void			BindMaterial(Material* material); //original parameter type: Material* 
		void			BindMesh(Mesh* mesh); //original parameter type: Mesh*
		
		void			SetClearColor(const float r, const float g, const float b, const float a);
		void			ClearBuffers();
		void			DrawMesh(Mesh* mesh);

	private:
		bool			IsShaderCompilationSuccessful(const GLuint shader) const;
		bool			IsProgramLinkingSuccessful(const GLuint program) const;
		void			DeletePrograms(const GLuint vertShader, const GLuint fragShader, const GLuint shaderProgram);
		void			DeletePrograms(const GLuint vertShader, const GLuint fragShader);
	};
}