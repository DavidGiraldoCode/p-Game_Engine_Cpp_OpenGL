#pragma once
#include <chrono>

/////////////////////////////////////////////////////////
// Engine class
/**
 * Owns Application
 * In charge of deleting Application, ALWAYS
 * No other class should delete Application
 * Only one owner
 */
/////////////////////////////////////////////////////////

namespace eng
{

	/* Forward declaration:
	* This tells the compiler: 
	* A class called Application exists I'll give you its full definition later.
	**/ 
	class Application;

	class Engine
	{
	public:
		Engine();
		~Engine();

		/// <summary>
		/// Executes Init in the game instance.
		/// 
		/// Separates "object exists" from "object ready for use"
		/// </summary>
		/// <returns></returns>
		bool Init();
		void Run();

		/// <summary>
		/// Note: the Game instance and heap-allocated memory is freed inside ~Engine
		/// </summary>
		void Shutdown(); // previously Destroy, logical shutdown only

		/// <summary>
		/// Ownership transferred happens here.
		/// Gets the pointer to the Game instance created by main.cpp,
		/// and Engine in charge of deleting Game.
		/// </summary>
		/// <param name="app"> The pointer created in main </param>
		void SetApplication(Application* app);	// ownership transfer 
		Application* GetApplication() const;	// non-owning access
	
	private:
		Application* m_app = nullptr;

		std::chrono::steady_clock::time_point m_lastTimePoint;
	};

}