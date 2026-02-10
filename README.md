# Game Engine Projec with C++ and OpenGL

## How to build the project
1. Run the following commands for Window Visual Studio 2022
```bash
cd /p-Game_Engine_Cpp_OpenGL
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
```
2. Go to `/build` and open `GameDevelopmentProject.sln`
3. Set `GameDevelopmentProject` as Start up Project
4. Inside VS, to go `main.cpp`, build solution and run


## Project directory
```bash
p-Game_Engine_Cpp_OpenGL/
├── CMakeLists.txt              # Root: defines the executable, links Engine
├── source/
│   ├── Game.h / .cpp
│   └── main.cpp                # Application entry point
├── engine/
│   ├── CMakeLists.txt          # Engine library: defines sources, links GLEW/GLFW
│   ├── source/                 # Engine .h and .cpp files
│   │   ├── eng.h               # Public facade header (include this from main)
│   │   ├── Engine.h / .cpp
│   │   ├── Application.h / .cpp
│   │   └── input/
│   │        └── InputManager.h / .cpp
│   └── thirdparty/
│       ├── glfw-3.4/           # GLFW (built from source)
│       └── glew/               # GLEW (built from source)
```