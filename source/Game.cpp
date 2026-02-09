#include <Game.h>

bool Game::Init()
{
	return true;
}

void Game::Update(float deltaTime)
{
	std::cout << "Delta time: " << deltaTime << "\n";
}

void Game::Destroy()
{
	
}