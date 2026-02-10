#include <iostream>
#include <eng.h>
#include <Game.h>

using eng::Engine;

int main(int argc, char *argv[])
{
    std::cout << "Ready to build a Game Engine\n";

    Engine& engine = Engine::GetInstance(); 
    engine.SetApplication(new Game()); // // Ownership pattern, You can also Game* game = new Game();

    if (engine.Init())
    {
        engine.Run();
    }

    engine.Shutdown();

    return 0;
}