#include "GraphicsAPI.h"
#include "ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng
{
	ShaderProgram* GraphicsAPI::CreateShaderProgram(const string& vertexSourceCode, const string& fragmentSourceCode)
	{

		// Create handlers to shaders and program
		GLuint vertexShader			= glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader		= glCreateShader(GL_FRAGMENT_SHADER);
		GLuint shaderProgramID		= glCreateProgram();

		// Load the source code to the shader handler
		const char* vertexShaderSourceCode		= vertexSourceCode.c_str();
		const char* fragmentShaderSourceCode	= fragmentSourceCode.c_str();

		glShaderSource(vertexShader, 1, &vertexShaderSourceCode, nullptr);
		glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, nullptr);

		// Compile the shader and validate
		glCompileShader(vertexShader);

		if (!IsShaderCompilationSuccessful(vertexShader))
			return nullptr;

		glCompileShader(fragmentShader);
		if (!IsShaderCompilationSuccessful(fragmentShader))
			return nullptr;

		// Attach to shader program
		glAttachShader(shaderProgramID, vertexShader);
		glAttachShader(shaderProgramID, fragmentShader);
		
		// Link shader program
		glLinkProgram(shaderProgramID);
		if (!IsProgramLinkingSuccessful(shaderProgramID))
			return nullptr;

		// Delete shader handlers
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// original: return std::make_shared<ShaderProgram>(shaderProgramID), Read about the learnings on this on Session notes Feb 19 2026
		return new ShaderProgram(shaderProgramID);
	}

	void GraphicsAPI::BindShaderProgram(ShaderProgram& shaderProgram)
	{
		// No nullptr check is needed because we are passing a ref.
			shaderProgram.Bind();
	}

	void GraphicsAPI::BindMaterial(Material& material)
	{
		// No nullptr check is needed because we are passing a ref.
		material.Bind();
	}


	void GraphicsAPI::BindMesh(Mesh& mesh)
	{
		// No nullptr check is needed because we are passing a ref.
		mesh.Bind();
	}

	GLuint GraphicsAPI::CreateVertexBuffer(const float* vertices, const size_t verticesCount)
	{
		GLuint vbo;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount, &vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vbo;
	}

	GLuint GraphicsAPI::CreateIndexBuffer(const uint32_t* indices, const size_t indicesCount)
	{
		GLuint ebo;

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicesCount, &indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return ebo;

	}

	void GraphicsAPI::SetClearColor(const float r, const float g, const float b, const float a)
	{
		glClearColor(r,g,b,a);
	}
	void GraphicsAPI::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicsAPI::DrawMesh(Mesh& mesh)
	{
		mesh.Draw();
	}

	bool GraphicsAPI::IsShaderCompilationSuccessful(const GLuint shader) const
	{
		GLint success;
		const unsigned int LOG_BUFFER_SIZE = 512;
		char infoLog[LOG_BUFFER_SIZE];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, LOG_BUFFER_SIZE, nullptr, infoLog);
			std::cerr << "ERROR: SHADER COMPILATION FAILED " << infoLog << '\n';
			return false;
		}

		return true;
	}

	bool GraphicsAPI::IsProgramLinkingSuccessful(const GLuint program) const
	{
		GLint success;
		const unsigned int LOG_BUFFER_SIZE = 512;
		char infoLog[LOG_BUFFER_SIZE];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		
		if (!success)
		{
			glGetProgramInfoLog(program, LOG_BUFFER_SIZE, nullptr, infoLog);
			std::cerr << "ERROR: SHADER PROGRAM LINKING FAILED " << infoLog << '\n';
			return false;
		}

		return true;
	}

}