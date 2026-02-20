#include <Game.h>
#include <GLFW/glfw3.h>
#include "eng.h"
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

    eng::ShaderProgram* shaderProgram = graphicsApi.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    m_material.SetShaderProgram(shaderProgram);

    constexpr unsigned RECT_VERTICES_DATA_SIZE = 24;

    float rectangleVertices[RECT_VERTICES_DATA_SIZE] =
    {
        //x     y       z       R       G       B
        0.1f,   0.1f,  0.0f,   1.0f,   0.0f,    0.0f,
       -0.1f,   0.1f,  0.0f,   0.0f,   1.0f,    0.0f,
       -0.1f,  -0.1f,  0.0f,   0.0f,   0.0f,    1.0f,
        0.1f,  -0.1f,  0.0f,   1.0f,   1.0f,    0.0f
    };

    constexpr unsigned RECT_INDICES_SIZE = 6;
    uint32_t rectangleIndices[RECT_INDICES_SIZE] =
    {
        0, 1, 2,
        0, 2, 3
    };

    eng::VertexLayout vertexLayout;
    vertexLayout.elementsCount = 2;
    vertexLayout.elements = new eng::VertexElement[vertexLayout.elementsCount]{};

    constexpr size_t POSITION = 0, COLOR = 1;

    vertexLayout.elements[POSITION] =
    {
        0,
        3,
        GL_FLOAT,
        0
    };
    vertexLayout.elements[COLOR] =
    {
        1,
        3,
        GL_FLOAT,
        sizeof(float) * 3
    };
    vertexLayout.stride = sizeof(float) * (vertexLayout.elements[POSITION].size + vertexLayout.elements[COLOR].size);

    m_mesh = new eng::Mesh(vertexLayout, &rectangleVertices[0], (size_t)4, &rectangleIndices[0], (size_t)6);

	return true;
}

void Game::Update(float deltaTime)
{
	//std::cout << "Delta time: " << deltaTime << "\n";
	
	auto& inputManager = Engine::GetInstance().GetInputManager();
	if(inputManager.IsKeyPressed(GLFW_KEY_A))
		std::cout << "Key[A]: Pressed! \n";

    eng::RenderCommand command;
    command.material = &m_material;
    command.mesh = m_mesh;

    auto& renderQueue = Engine::GetInstance().GetRenderQueue();
    renderQueue.Submit(command);
}

void Game::Destroy()
{

}