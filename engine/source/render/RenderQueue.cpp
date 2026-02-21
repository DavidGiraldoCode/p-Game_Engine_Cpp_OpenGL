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

	
	// TODO: double check if this solves issue 3
	void RenderQueue::Submit(const RenderCommand& command)
	{

		// Invariance
		if (m_commandsCount >= RENDER_COMMANDS_SIZE)
			return;

		m_usedCommands[m_commandsCount++] = true;

		// It will try to find space to add a Render Command
		for (size_t i = 0; i < RENDER_COMMANDS_SIZE; i++)
		{
			if (!m_usedCommands[i])
			{
				// Would it create a deep copy?
				// m_renderCommands[i] = command;
				m_renderCommands[i].mesh		= command.mesh;
				m_renderCommands[i].material	= command.material;
				break;
			}
		}
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