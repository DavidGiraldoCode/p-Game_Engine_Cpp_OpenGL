#include <Game.h>
#include <GLFW/glfw3.h>
using eng::Engine;

bool Game::Init()
{
   //////////////////////////////////////////////////////////////
   // Shader sources
   //////////////////////////////////////////////////////////////
    std::string vertexShaderSource = R"(
        #version 330 core
        
        uniform vec3 uOffSet;

        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;
        
        out vec3 colorUV;

        void main()
        {

            gl_Position = vec4( position.x + uOffSet.x , 
                                position.y + uOffSet.y, 
                                0.0, 
                                1.0);
            colorUV = color;
        }    

    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        
        uniform vec4 uColor;
        
        in vec3 colorUV;
        out vec4 FragColor;

        void main()
        {
            //FragColor = vec4(colorUV.r, colorUV.g, colorUV.b, 1.0) + uColor;
            FragColor = vec4(uColor.r, uColor.g, uColor.b, 1.0);
        }
    )";

    // First time the GraphicsAPI gets instantiated

    auto& graphicsApi = Engine::GetInstance().GetGraphicsAPI();

    auto shaderProgram = graphicsApi.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

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