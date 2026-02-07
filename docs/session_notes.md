# Session Notes - DevLogs

This is not meant to have value for users of this code but to the author's learning journey. For information on how to use this Engine, go to the Wiki.

## Feb 7 2026
/ **TODO:** Create a new branch `expose_engine_lib`
- The Engine code is treated as an external library. In the GameEngineProject, you include the headers from the engine lib, and a Game class extends from Application.  
- I have not added or exposed the header files just yet. That's the next thing.  
- Also, I need to read about the implications of the functions the instructor is calling after using smart pointers. I intend to use raw pointers and practice handling memory on my own.

**Assingment:** Render 5 unique objects (2D).
- [x] Use a different color/shape per object 
- [x] One object should animate over time
- [x] One object should response to keyboard input


## Feb 6 2026
- Uniforms are variables that can be set at runtime by the CPU but do not change throughout the draw call. One needs to get the location of the variables from the already compiled shader program.

## Feb 5 2026
<img src="hello_triangle.png" alt="Hello Triangle" style="width: 480px; height: auto;">

- A game engine needs to display a window, which is its primary function. However, OpenGL itself is not a window library; that's where GLFW comes in. We use GLFW to manage the native behavior of the window and handle user inputs, while also setting it as the rendering context.

- OpenGL operates as a state machine and can only render one buffer of vertices at a time. This means that binding and unbinding resources is crucial to inform OpenGL what the CPU is attempting to render at any specific moment.

- It's also important to remember that OpenGL generates triangles in a counterclockwise orientation, with the z-axis pointing towards the camera.