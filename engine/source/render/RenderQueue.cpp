#include "render/RenderQueue.h"
#include "graphics/GraphicsAPI.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng
{

	RenderQueue::~RenderQueue()
	{
		// For the record, this is a commun mistake, a raw array is NOT heap allocated unless it
		// was created using new. Even if what it stores are pointers to heap allocated memory
		// delete[] m_renderCommands;
	}

	
	void RenderQueue::Submit(const RenderCommand& command)
	{
		// This local assgination give the static analysis engine a safety way to validate
		// against potential buffer overrun. All arrays using this index are safe.
		const size_t index = m_commandsCount;

		// Invariance
		if (index >= RENDER_COMMANDS_SIZE)
		{
			std::cerr << "ERROR: RenderQueue is full! Command dropped.\n";
			return;
		}

		// Shallow copies here, only copying the pointers to the same mesh and material objects
		m_renderCommands[index].mesh		= command.mesh;
		m_renderCommands[index].material	= command.material;
		m_usedCommands[index] = true;

		m_commandsCount++;
	}

	void RenderQueue::Draw(GraphicsAPI& graphicsApi)
	{
		// original for(auto& command : m_renderCommands)
		for (size_t i = 0; i < m_commandsCount; i++)
		{
			graphicsApi.BindMaterial( m_renderCommands[i].material );
			graphicsApi.BindMesh( m_renderCommands[i].mesh);

			graphicsApi.DrawMesh( m_renderCommands[i].mesh);

			m_usedCommands[i] = false;
		}

		// original m_renderCommands.clear() to clean up the std::vector<RenderCommand>
		m_commandsCount = 0;
	}
}