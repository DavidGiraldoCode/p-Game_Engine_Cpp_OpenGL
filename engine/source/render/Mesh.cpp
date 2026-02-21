#include "render/Mesh.h"
#include "Engine.h"

namespace eng
{
	Mesh::Mesh(	const VertexLayout&		layout,
				const float*			vertices,
				const size_t			verticesCount,
				const uint32_t*			indices,
				const size_t			indicesCount)
	{
		// TODO: do they create deep copies?
		// The instructor does the same, but I am not sure if by using std:: objects he gets
		// the deep copy
		m_vertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		m_VBO = graphicsAPI.CreateVertexBuffer(vertices, verticesCount);
		m_EBO = graphicsAPI.CreateIndexBuffer(indices, indicesCount);

		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		// Loop over the array of elements in the vertex layout

		for (size_t i = 0; i < layout.elementsCount; i++)
		{
			// Define how to interprete the data
			glVertexAttribPointer(	layout.elements[i].index, 
									layout.elements[i].size,
									layout.elements[i].type,
									GL_FALSE,
									layout.stride,
									(void*) layout.elements[i].offset);

			glEnableVertexAttribArray(layout.elements[i].index);

		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_vertexCount = verticesCount;//(verticesCount * sizeof(float)) / m_vertexLayout.stride;
		m_indexCount = indicesCount;
	}

	Mesh::Mesh(	const VertexLayout&		layout,
				const float*			vertices,
				const size_t			verticesCount)
	{
		m_vertexLayout = layout; // TODO: do they create deep copies

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		m_VBO = graphicsAPI.CreateVertexBuffer(vertices, verticesCount);

		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		// Loop over the array of elements in the vertex layout

		for (size_t i = 0; i < layout.elementsCount; i++)
		{
			// Define how to interprete the data
			glVertexAttribPointer(layout.elements[i].index,
				layout.elements[i].size,
				layout.elements[i].type,
				GL_FALSE,
				layout.stride,
				(void*) layout.elements[i].offset);

			glEnableVertexAttribArray(layout.elements[i].index);

		}

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_vertexCount = verticesCount;//(verticesCount * sizeof(float)) / m_vertexLayout.stride;

	}

	Mesh::~Mesh()
	{
		DeleteBuffers();
	}

	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}

	void Mesh::Draw()
	{
		if (m_indexCount > 0)
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	}

	void Mesh::DeleteBuffers()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		if (m_EBO != 0)
			glDeleteBuffers(1, &m_EBO);
	}
}