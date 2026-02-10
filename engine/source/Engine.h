#pragma once
#include <chrono>
#include <iostream>

/////////////////////////////////////////////////////////
// Engine class
/**
 * Owns Application
 * In charge of deleting Application, ALWAYS
 * No other class should delete Application
 * Only one owner
 */
/////////////////////////////////////////////////////////

struct GLFWwindow; //TODO review why this is declare here and not inside the namespace

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
		bool Init(unsigned int width, unsigned int height);
		
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
		std::chrono::steady_clock::time_point m_lastTimePoint;
		
		Application*	m_app		= nullptr;
		GLFWwindow*		m_window	= nullptr;

		/// <summary>
		/// Uses GLWF to create the window and set the OpenGL context
		/// </summary>
		/// <returns>True is window succeed</returns>
		bool CreateWindow( const unsigned int width, const unsigned int height, const char* title);

		void UpdateDeltaTime(float& timeToUpdate);
	};

}