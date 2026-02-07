#pragma once
#include <chrono>

namespace engine
{
	// Forward declaration of the application class
	class Application;

	class Engine
	{
	public:
		Engine();
		~Engine();
		bool Init();
		void Run();
		void Destroy();

		void SetApplication(Application *app);
		Application* GetApplication();
	
	private:
		Application* m_app = nullptr;
		std::chrono::steady_clock::time_point m_lastTimePoint;
	};

}