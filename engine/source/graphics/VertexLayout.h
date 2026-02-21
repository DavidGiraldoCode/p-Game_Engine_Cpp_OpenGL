#pragma once
#include <GL/glew.h>
#include <cstdint>

namespace eng
{
	/// <summary>
	/// The raw description of the memory layout that represents the vertex data
	/// An element is a vertex.
	/// Original member type of offset was uint32_t, but in 64-bit systems get truncated, read NOTE
	/// </summary>
	struct VertexElement
	{
		GLuint		index	= 0; // Attribute location in the shader e.g. (location = 0)
		GLuint		size	= 0; // Number of components that attribute has e.g. (x,y) or (x,y,z,w)
		GLuint		type	= 0; // The OpenGL type of data of the attributes e.g GL_FLOAT
		size_t		offset	= 0; // How many bytes from the start of the vextex the first data point of the attribute is
	};

	/// <summary>
	/// Container for the list of vertices layout
	/// </summary>
	struct VertexLayout
	{
		VertexElement*		elements		= nullptr;	// Original member type: std::vector<VertexElement>
		uint32_t			elementsCount	= 0;		//
		uint32_t			stride			= 0;		//
		
		~VertexLayout()
		{
			if(elements != nullptr)
				delete[] elements;
		}
	};
}

/**
NOTE about offset in the glVertexAttribPointer(..., (void*)offset );

OpenGL treats the offset as a pointer-sized value, not just a number.
A pointer-size value is an integer type large enough to store a memory address.
32-bit machine -> pointer = 4 bytes
64-bit machine -> pointer = 8 bytes
So the type should convert to a point without trunccation

For OpenGL, void* pointer is not a real pointer, its only the offset in bytes para pointers have, 
which will change depending on the machine.
integer -> pretend pointer -> GPU interprets as offset

size_t type is used to represent size of memory objects
*/