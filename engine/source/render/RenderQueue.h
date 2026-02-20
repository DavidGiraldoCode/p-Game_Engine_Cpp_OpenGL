#pragma once

namespace eng
{
	class Mesh;
	class Material;
	class GraphicsAPI;

	struct RenderCommand
	{
		Mesh*		mesh		= nullptr;
		Material*	material	= nullptr;
	};

	class RenderQueue
	{
	public:

		~RenderQueue();

		void Submit(RenderCommand& command);
		void Draw(GraphicsAPI& graphicsApi);

	private:
		static const size_t RENDER_COMMANDS_SIZE = 100;
		// TODO: this one is tricky, because it may grow dynamically, for now, it will be stack allocated
		RenderCommand* m_renderCommands[RENDER_COMMANDS_SIZE] = {nullptr};

	};
}