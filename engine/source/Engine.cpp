#include "Engine.h"
#include "Application.h"

namespace eng
{
	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
		delete m_app;
		m_app = nullptr;
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
	
	void Engine::Shutdown() // Previously Destroy
	{
		if (m_app)
		{
			m_app->Destroy(); // logical clean up only
		}
	
	};

	void Engine::SetApplication(Application *app)
	{
		delete m_app; 	// Delete previous
		m_app = app;	// Takes ownership
	};

	Application* Engine::GetApplication() const
	{
		return m_app;
	}
}
