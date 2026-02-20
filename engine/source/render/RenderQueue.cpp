#include "render/RenderQueue.h"
#include "graphics/GraphicsAPI.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace eng
{

	RenderQueue::~RenderQueue()
	{
		delete[] m_renderCommands;
	}

	
	void RenderQueue::Submit(RenderCommand& command)
	{
		// It will try to find space to add a Render Command
		for (size_t i = 0; i < RENDER_COMMANDS_SIZE; i++)
		{
			if (m_renderCommands[i] == nullptr)
			{
				m_renderCommands[i] = &command;
				break;
			}
		}
	}

	void RenderQueue::Draw(GraphicsAPI& graphicsApi)
	{
		for (size_t i = 0; i < RENDER_COMMANDS_SIZE; i++)
		{
		
			if (m_renderCommands[i] != nullptr)
			{
				graphicsApi.BindMaterial(*m_renderCommands[i]->material);
				graphicsApi.BindMesh(*m_renderCommands[i]->mesh);
				graphicsApi.DrawMesh(*m_renderCommands[i]->mesh);
			}
		}

		for (size_t i = 0; i < RENDER_COMMANDS_SIZE; i++)
		{
			if (m_renderCommands[i] != nullptr)
			{
				m_renderCommands[i] = nullptr;
			}
		}
	}
}