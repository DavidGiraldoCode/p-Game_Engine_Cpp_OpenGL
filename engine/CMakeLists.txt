cmake_minimum_required(VERSION 3.10)

project(Engine)

set(PROJECT_SOURCE_FILES
    source/Engine.h
    source/Engine.cpp
    source/Application.h
    source/Application.cpp
)
include_directories(source)

# Including the Engine as a library
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})


# --------------------------------------------------------------------- Add GLFW Library
# Configure and build GLFW from sources, placing build artifacts in /glfw_build
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
# Expose include/ so we can use #include <GLFW/glfw3.h> in the cpp files
include_directories(thirdparty/glfw-3.4/include)

# --------------------------------------------------------------------- Add Glew Library
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
# Builds GLEW and places the artifacts in /glew_build
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
# Adds GLEW headers to the search path
include_directories(thirdparty/glew/include)

# Disable GLEW utilities we don't need
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew PROPERTY FOLDER GLEW)


# Link all thirdparty libraries, links the app with GLFW and static GLEW (hence glew_s)
target_link_libraries(${PROJECT_NAME} glfw glew_s)