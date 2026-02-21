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
				const size_t			totalFComponentsCount,
				const unsigned int*		indices,
				const size_t			indicesCount);

		Mesh(	const VertexLayout&		layout, 
				const float*			vertices, 
				const size_t			totalFComponentsCount);
		
		// Disable copy constructor and assignment
		// Wich tells the compiler not to generate a move constuctor or move assignment
		// Meshes can only be created and distroy in place.
		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;

		~Mesh();

		void Bind();
		void Draw();

	private:
		VertexLayout	m_vertexLayout;
		
										// in-class member initializer applies before constuctor's body runs
		GLuint			m_VBO			 = 0; // Vertex Buffer Object
		GLuint			m_EBO			 = 0; // Elements Buffers Object (indeces)
		GLuint			m_VAO			 = 0; // Vertex Attributes Object
		
		size_t			m_vertexCount	 = 0;
		size_t			m_indexCount	 = 0;
		
		void DeleteBuffers(); // Only the destructor can call this

	};
}