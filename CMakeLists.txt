cmake_minimum_required(VERSION 3.10)

# Creates a variable called PROJECT_NAME
project(GameDevelopmentProject)

# Defines the app sources
set(PROJECT_SOURCE_FILES
    source/main.cpp
)

# Adds source/ to the header searc path
include_directories(source)
# Build executable target called GameDevelopmentProject
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# -------- GLEW and GLFW are included through the Engine module, so we link the Engine library

# Add the directory
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")

target_link_libraries(${PROJECT_NAME}
    Engine
)


