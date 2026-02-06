#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

// TODO
/*
void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    switch(key)

}
*/

int main(int argc, char* argv[])
{
    std::cout << "Hello world! \n";

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
    // TODO: 
    //glfwSetKeyCallback(window, keyCallback);

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
        0.5f,   0.5f,  0.0f,   1.0f,   0.0f,    0.0f,
       -0.5f,   0.5f,  0.0f,   0.0f,   1.0f,    0.0f,
       -0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,    1.0f,
        0.5f,  -0.5f,  0.0f,   1.0f,   1.0f,    0.0f
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
    // Generate buffers
    ////////////////////////////////////////////////////////
    // vertex buffer object, sending memory to the VRAM
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), &rectangleIndices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Define the attributes of the data
    glGenVertexArrays(1, &vao);
    
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
    // Vertex Shader
    //////////////////////////////////////////////////////////////
    // Load the shader program
    std::string vertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        out vec3 colorUV;

        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
            colorUV = color;
        }    

    )";

    // Create a handler for the shader source
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    constexpr unsigned LOG_BUFFER = 512;
    char infoLog[LOG_BUFFER];

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, LOG_BUFFER, nullptr, infoLog);
        std::cerr << "ERROR: VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << "\n";
    }
    else
        std::cout << "VERTEX_SHADER_COMPILATION_SUCCESSFUL " << "\n";

    //////////////////////////////////////////////////////////////
    // Fagment Shader
    //////////////////////////////////////////////////////////////
    std::string fragmentShaderSource = R"(
        #version 330 core
        
        uniform vec4 uColor;
        
        in vec3 colorUV;
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(colorUV.r, colorUV.g, colorUV.b, 1.0) + uColor;
        }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, LOG_BUFFER, nullptr, infoLog);
        std::cerr << "ERROR: FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << "\n";
    }
    else
        std::cout << "FRAGMENT_SHADER_COMPILATION_SUCCESSFUL " << "\n";

    GLuint shaderProgram = glCreateProgram();
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
    // Set uniforms
    ///////////////////////////////////////////////////////////////////////////////
    GLuint uColorLocation = glGetUniformLocation(shaderProgram, "uColor");

    // Start main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform4f(uColorLocation, 0.5f, 0.5f, 0.5f, 1.0f);
        glBindVertexArray(vao);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free resources
    glfwTerminate();

    return 0;
}