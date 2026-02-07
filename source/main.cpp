#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <chrono>

struct Position // 8 bytes
{
    float x = 0.f; // 4 bytes
    float y = 0.f; // 4 butes
};

struct Color // 12 bytes
{
    float r = 1.f;
    float g = 1.f;
    float b = 1.f;
};


const double PI = 3.14159265358979323846;

constexpr unsigned STATIC_SHAPES_SIZE = 3;
constexpr unsigned SHAPE_COLORS_SIZE = 5;
Position    offSet;
Position    staticShapes[STATIC_SHAPES_SIZE]; // 8 * 3 = 24 bytes
Color       colors[SHAPE_COLORS_SIZE]; // 60 bytes

Position    animatedOffSet = {0.1f, 0.f};
float rotationSpeed = 45.f;
float roationDegree = 0.f;

float DTR(float degree) { return degree* (2 * PI / 360.f); }

void rotate(float degree, Position *posToRotate)
{
    if (posToRotate == nullptr)
        return;

    Position newPos;
    float radian = DTR(degree);

    newPos.x = posToRotate->x * std::cos(radian) - posToRotate->y * std::sin(radian);
    newPos.y = posToRotate->x * std::sin(radian) + posToRotate->y * std::cos(radian);

    posToRotate->x = newPos.x;
    posToRotate->y = newPos.y;
}

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{

    if (action == GLFW_PRESS)
    {
        char* keyMessage = "";
        switch (key)
        {
        case GLFW_KEY_UP:
            keyMessage = "up";
            offSet.y += 0.1f;
            break;

        case GLFW_KEY_DOWN:
            keyMessage = "down";
            offSet.y -= 0.1f;
            break;

        case GLFW_KEY_RIGHT:
            keyMessage = "right";
            offSet.x += 0.1f;
            break;

        case GLFW_KEY_LEFT:
            keyMessage = "left";
            offSet.x -= 0.1f;
            break;

        default:
            break;
        }

        std::cout << keyMessage << '\n';

    }

}


int main(int argc, char* argv[])
{
    std::cout << "Hello world! \n";
    std::cout << "colors size: " << sizeof(colors) << " bytes \n";


    /////////////////////////////////////////////////////////////////////////////////////////
    // Window API
    /////////////////////////////////////////////////////////////////////////////////////////
    
    // Initialize the window library
    if (!glfwInit())
        return -1;
    else
        std::cout << "GLFW Initialized! \n";

    // Define the OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create the window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "David Game Engine", nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    else
        std::cout << "Window created successfully! \n";

    // Listen to events
    glfwSetKeyCallback(window, keyCallback);

    // Set the window are redering context
    glfwMakeContextCurrent(window);

    // Initialize glew to use OpenGL functions
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // Vertices and Buffer
    //////////////////////////////////////////////////////////////
    constexpr unsigned VERTICES_DATA_SIZE = 18;

    float triangleVertices[VERTICES_DATA_SIZE] =
    {
        //x     y       z       R       G       B
        0.5f,   0.5f,  0.0f,   1.0f,   0.0f,    0.0f,
       -0.5f,  -0.5f,  0.0f,   0.0f,   1.0f,    0.0f,
        0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,    1.0f
    };

    constexpr unsigned RECT_VERTICES_DATA_SIZE = 24;

    float rectangleVertices[RECT_VERTICES_DATA_SIZE] =
    {
        //x     y       z       R       G       B
        0.1f,   0.1f,  0.0f,   1.0f,   0.0f,    0.0f,
       -0.1f,   0.1f,  0.0f,   0.0f,   1.0f,    0.0f,
       -0.1f,  -0.1f,  0.0f,   0.0f,   0.0f,    1.0f,
        0.1f,  -0.1f,  0.0f,   1.0f,   1.0f,    0.0f
    };

    // Store the indices to re-use vertex data
    constexpr unsigned RECT_INDICES_SIZE = 6;
    unsigned int rectangleIndices[RECT_INDICES_SIZE] =
    {
        0, 1, 2,
        0, 2, 3
    };

    std::cout << "Size of rectangeVertices: " << sizeof(rectangleVertices) << "\n";

    ////////////////////////////////////////////////////////
    // Declare buffers
    ////////////////////////////////////////////////////////

    GLuint vbo; // Vertex Buffer Object

    GLuint vao; // Vertex Attributes Object

    GLuint ebo; // Elements Buffer Object

    ////////////////////////////////////////////////////////
    // Generate buffers - vertex buffer object, sending memory to the VRAM
    ////////////////////////////////////////////////////////

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    
    // Buffering data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), &rectangleIndices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Define the attributes of the data
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Define how to interpret the data
    //                    index    count    type      normalized    stride                      off-set
    glVertexAttribPointer( 0,       3,      GL_FLOAT, false,        6 * sizeof(float),  (void*)  0                  );
    glVertexAttribPointer( 1,       3,      GL_FLOAT, false,        6 * sizeof(float),  (void*) (3 * sizeof(float)) );
    
    glEnableVertexAttribArray(0); // Note for future me, this step is key, otherwise OpenGL wont know how to read the vertex data
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

    //////////////////////////////////////////////////////////////
    // Vertex and Fragment Shader Compilation
    //////////////////////////////////////////////////////////////
    
    // Create a handler for the shader source and shader programs
    GLuint vertexShader     = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader   = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgram    = glCreateProgram();
    GLint  success;
    
    
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    const char* fragmentShaderCStr = fragmentShaderSource.c_str();
   
    // Load the shader program
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
    
    // Compile shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Validate compilation
    constexpr unsigned LOG_BUFFER = 512;
    char infoLog[LOG_BUFFER];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, LOG_BUFFER, nullptr, infoLog);
        std::cerr << "ERROR: VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << "\n";
    }
    else
        std::cout << "VERTEX_SHADER_COMPILATION_SUCCESSFUL " << "\n";

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, LOG_BUFFER, nullptr, infoLog);
        std::cerr << "ERROR: FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << "\n";
    }
    else
        std::cout << "FRAGMENT_SHADER_COMPILATION_SUCCESSFUL " << "\n";

    //////////////////////////////////////////////////////////////
    // Shader Program Setup
    //////////////////////////////////////////////////////////////
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, LOG_BUFFER, nullptr, infoLog);
        std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED: " << infoLog << "\n";
    }
    else
        std::cout << "SHADER_PROGRAM_LINKING_SUCCESSFUL " << "\n";

    // Release memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ///////////////////////////////////////////////////////////////////////////////
    // Set uniforms in the shader program
    ///////////////////////////////////////////////////////////////////////////////
    GLuint uColorLocation = glGetUniformLocation(shaderProgram, "uColor");
    GLuint uOffSetLocation = glGetUniformLocation(shaderProgram, "uOffSet");


    
    staticShapes[0].x = 0.25f;
    staticShapes[0].y = 0.25f;

    staticShapes[1].x = 0.25f;
    staticShapes[1].y = -0.25f;

    staticShapes[2].x = -0.25f;
    staticShapes[2].y = 0.25f;

    colors[0] = { 1.0f, 0.0f, 0.0f };
    colors[1] = { 0.0f, 1.0f, 0.0f };
    colors[2] = { 0.0f, 0.0f, 1.0f };
    colors[3] = { 1.0f, 0.0f, 1.0f };
    colors[4] = { 0.0f, 1.0f, 1.0f };

    auto lastTime = std::chrono::high_resolution_clock::now();

    // Start main loop
    while (!glfwWindowShouldClose(window))
    {

        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        for (rsize_t i = 0; i < 5; i++)
        {
            
            if (i == 0) // Shape that reacts to input
                glUniform3f(uOffSetLocation, offSet.x, offSet.y, 0.f);
            else if (i == 1) // Shape that is animated
            {

                roationDegree = rotationSpeed * deltaTime;// += rotationSpped;
                rotate(roationDegree, &animatedOffSet);
                glUniform3f(uOffSetLocation, animatedOffSet.x, animatedOffSet.y, 0.f);

            }
            else // Static shapes
            {
                glUniform3f(uOffSetLocation, staticShapes[(int)i - 2].x, staticShapes[(int)i - 2].y, 0.f);
            }
            
            glUniform4f(uColorLocation, colors[i].r, colors[i].g, colors[i].b, 1.0f);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //glUniform3f(uOffSetLocation, offSet.x + 0.1f, offSet.y + 0.1f, offSet.z);
            //glUniform4f(uColorLocation, 0.9f, 0.9f, 0.9f, 1.0f);
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free resources
    //glDeleteBuffers()
    glDeleteProgram(shaderProgram);
    glfwTerminate();
   

    return 0;
}