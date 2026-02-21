#pragma once
#include "GL/glew.h"
#include "graphics/VertexLayout.h"

namespace eng
{
	class Mesh
	{
	public:
		/// <summary>
		/// Original parameters:
		/// const VertexLayout&	layout
		/// const std::vector<float>& vertices
		/// const std::vector<float>& indices
		/// </summary>
		Mesh(	const VertexLayout&		layout, 
				const float*			vertices, 
				const size_t			verticesCount,
				const uint32_t*			indices,
				const size_t			indicesCount);

		Mesh(	const VertexLayout&		layout, 
				const float*			vertices, 
				const size_t			verticesCount);
		
		// Disable copy and assignment
		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;

		~Mesh();

		void Bind();
		void Draw();

	private:
		VertexLayout	m_vertexLayout;
		
		GLuint			m_VBO			 = 0; // Vertex Buffer Object
		GLuint			m_EBO			 = 0; // Elements Buffers Object (indeces)
		GLuint			m_VAO			 = 0; // Vertex Attributes Object
		
		size_t			m_vertexCount	 = 0;
		size_t			m_indexCount	 = 0;
		
		void DeleteBuffers(); // Only the destructor can call this

	};
}