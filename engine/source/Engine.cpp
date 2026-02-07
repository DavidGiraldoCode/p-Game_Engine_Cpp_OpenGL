#include "Engine.h"
#include "Application.h"

namespace engine
{
	Engine::Engine()
	{

	}

	Engine::~Engine()
	{

	}

	bool Engine::Init()
	{
		if (!m_app)
			return false;

		return m_app->Init();
	};

	void Engine::Run()
	{
	
		if (!m_app)
			return;

		m_lastTimePoint = std::chrono::high_resolution_clock::now();

		while (!m_app->NeedsToBeClosed())
		{
			auto now = std::chrono::high_resolution_clock::now();
			float delatTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
			m_lastTimePoint = now;

			m_app->Update(delatTime);

		}
	};
	
	void Engine::Destroy()
	{
		if (m_app)
		{
			m_app->Destroy();
			m_app = nullptr;
		}
	
	};

	void Engine::SetApplication(Application *app)
	{
		// TODO: Validate this when using raw pointers instead of smart pointers
		m_app = app;
	};

	Application* Engine::GetApplication()
	{
		// TODO: Validate this when using raw pointers instead of smart pointers
		return m_app;
	}
}
