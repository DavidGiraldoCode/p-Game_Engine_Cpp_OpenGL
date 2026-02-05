# Session Notes - DevLogs

This is not meant to have value for users of this code but to the author's learning journey. For information on how to use this Engine, go to the Wiki.

## Feb 5 2026
<img src="hello_triangle.png" alt="Hello Triangle" style="width: 480px; height: auto;">

- A game engine needs to display a window, which is its primary function. However, OpenGL itself is not a window library; that's where GLFW comes in. We use GLFW to manage the native behavior of the window and handle user inputs, while also setting it as the rendering context.

- OpenGL operates as a state machine and can only render one buffer of vertices at a time. This means that binding and unbinding resources is crucial to inform OpenGL what the CPU is attempting to render at any specific moment.

- It's also important to remember that OpenGL generates triangles in a counterclockwise orientation, with the z-axis pointing towards the camera.