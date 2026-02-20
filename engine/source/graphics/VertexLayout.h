#pragma once
#include <cstdint>

namespace eng
{
	/// <summary>
	/// The raw description of the memory layout that represents the vertex data
	/// An element is a vertex
	/// </summary>
	struct VertexElement
	{
		GLuint		index	= 0;
		GLuint		size	= 0;
		GLuint		type	= 0;
		uint32_t	offset	= 0;
	};

	/// <summary>
	/// Container for the list of vertices layout
	/// </summary>
	struct VertexLayout
	{
		VertexElement*		elements		= nullptr;	// Original std::vector
		uint32_t			elementsCount	= 0;		//
		uint32_t			stride			= 0;		//
		
		~VertexLayout()
		{
			delete[] elements;
		}
	};
}