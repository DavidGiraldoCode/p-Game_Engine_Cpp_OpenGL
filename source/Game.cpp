#include <Game.h>
#include <GLFW/glfw3.h>
using eng::Engine;

bool Game::Init()
{
	return true;
}

void Game::Update(float deltaTime)
{
	//std::cout << "Delta time: " << deltaTime << "\n";
	
	auto& inputManager = Engine::GetInstance().GetInputManager();
	if(inputManager.IsKeyPressed(GLFW_KEY_A))
		std::cout << "Key[A]: Pressed! \n";
}

void Game::Destroy()
{
	
}