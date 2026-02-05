#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

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
    constexpr unsigned VERTICES_DATA_SIZE = 9;

    float vertices[VERTICES_DATA_SIZE] =
    {
        //x     y   z
        0.0f,   0.5f,  0.0f,
       -0.5f,  -0.5f,  0.0f,
        0.5f,  -0.5f,  0.0f
    };

    std::cout << "Size of vertices: " << sizeof(vertices) << "\n";

    // vertex buffer object, sending memory to the VRAM
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Define the attributes of the data
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Define how to interpret the data
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Note for future me, this step is key, otherwise OpenGL wont know how to read the vertex data

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //////////////////////////////////////////////////////////////
    // Vertex Shader
    //////////////////////////////////////////////////////////////
    // Load the shader program
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
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
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
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

    ///


    // Start main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free resources
    glfwTerminate();

    return 0;
}