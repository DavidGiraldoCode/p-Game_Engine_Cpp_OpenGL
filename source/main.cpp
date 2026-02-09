#include <iostream>
#include <eng.h>
#include <Game.h>

int main(int argc, char *argv[])
{
    std::cout << "Ready to build a Game Engine\n";

    // Ownership pattern
    Game* game = new Game();
    eng::Engine engine;
    engine.SetApplication(game);

    if (engine.Init())
    {
        engine.Run();
    }

    engine.Shutdown();

    return 0;
}