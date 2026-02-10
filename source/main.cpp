#include <iostream>
#include <eng.h>
#include <Game.h>

int main(int argc, char *argv[])
{
    std::cout << "Ready to build a Game Engine\n";

    // Ownership pattern
    // Game* game = new Game();
    
    // Ownership pattern
    eng::Engine engine;
    engine.SetApplication(new Game());

    if (engine.Init(1280,720))
    {
        engine.Run();
    }

    engine.Shutdown();

    return 0;
}