#pragma once

namespace eng
{
	class Mesh
	{
	public:
		Mesh() = delete;

	private:
		GLuint m_VBO; // Vertex Buffer Object
		GLuint m_EBO; // Elements Buffers Object
		GLuint m_VAO; // Vertex Attributes Object
	};
}