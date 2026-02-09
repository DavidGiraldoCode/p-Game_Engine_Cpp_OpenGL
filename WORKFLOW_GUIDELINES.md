# Workflow Guidelines

How to add files, manage dependencies, and keep the build working.

---

## Project Structure

```
p-Game_Engine_Cpp_OpenGL/
├── CMakeLists.txt              # Root: defines the executable, links Engine
├── source/
│   └── main.cpp                # Application entry point
├── engine/
│   ├── CMakeLists.txt          # Engine library: defines sources, links GLEW/GLFW
│   ├── source/                 # Engine .h and .cpp files
│   │   ├── eng.h               # Public facade header (include this from main)
│   │   ├── Engine.h / .cpp
│   │   └── Application.h / .cpp
│   └── thirdparty/
│       ├── glfw-3.4/           # GLFW (built from source)
│       └── glew/               # GLEW (built from source)
└── build/                      # Generated build artifacts (gitignored)
```

---

## Adding New Source Files

### Engine files (inside `engine/source/`)

1. Create the `.h` and `.cpp` files in `engine/source/`
2. Register them in `engine/CMakeLists.txt` under `PROJECT_SOURCE_FILES`:
   ```cmake
   set(PROJECT_SOURCE_FILES
       source/Engine.h
       source/Engine.cpp
       source/Application.h
       source/Application.cpp
       source/eng.h
       source/YourNewFile.h      # <-- add here
       source/YourNewFile.cpp    # <-- add here
   )
   ```
3. If the new header should be available to consumers (main.cpp), add it to `eng.h`:
   ```cpp
   #include "YourNewFile.h"
   ```
4. Re-run CMake (see "CMake Rebuild Pipeline" below)

### Application files (inside `source/`)

1. Create the `.h` and `.cpp` files in `source/`
2. Register them in the root `CMakeLists.txt` under `PROJECT_SOURCE_FILES`:
   ```cmake
   set(PROJECT_SOURCE_FILES
       source/main.cpp
       source/Game.h             # <-- add here
       source/Game.cpp           # <-- add here
   )
   ```
3. Re-run CMake

---

## CMake Rebuild Pipeline

### When to re-run CMake (regenerate the VS project)

You **must** re-run CMake when you:
- Add or remove source files from a `CMakeLists.txt`
- Add a new library or dependency
- Change any CMake variable or option

Command (from project root):
```bash
cmake -S . -B build -G "Visual Studio 17 2022"
```

### When you only need to Build (no CMake re-run)

You only need to build (not re-run CMake) when you:
- Edit existing `.h` or `.cpp` files
- Change code within already-registered files

Build from command line:
```bash
cmake --build build
```
Or just press **Ctrl+B** / **Build Solution** in Visual Studio.

### Full clean rebuild

If things get into a bad state:
```bash
rm -rf build
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build
```

---

## Where to Create Files

**Recommended: Create files from the terminal (Git Bash) or file explorer**, then register them in CMakeLists.txt, then re-run CMake. This is the most reliable method.

**Creating files from Visual Studio 2022:**
- Files created via VS "Add New Item" may be placed in the `build/` directory or marked as "Not included" because VS doesn't know to put them in `source/` or `engine/source/`.
- If you create a file from VS, make sure it's saved to the correct source directory, add it to the relevant CMakeLists.txt, then re-run CMake.

**Summary:** Always ensure new files end up in the right source folder (`source/` or `engine/source/`) and are listed in the corresponding CMakeLists.txt.

---

## Adding a Third-Party Library

Follow the existing pattern used by GLFW and GLEW in `engine/CMakeLists.txt`:

1. Place the library source in `engine/thirdparty/<library-name>/`
2. Add to `engine/CMakeLists.txt`:
   ```cmake
   # Add the library
   add_subdirectory(thirdparty/<library-name> "${CMAKE_CURRENT_BINARY_DIR}/<library>_build")

   # If Engine source files need its headers internally:
   include_directories(thirdparty/<library-name>/include)

   # Link it to the Engine target
   target_link_libraries(${PROJECT_NAME} <library-target-name>)
   ```
3. Re-run CMake

---

## How the Engine Library is Exposed

The Engine uses `target_include_directories` with `PUBLIC` scope:

```cmake
target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)
```

This means any target that links against `Engine` (like the main executable) automatically gets the engine headers in its include path. You do **not** need to add `include_directories(engine/source)` in the root CMakeLists.txt — the `target_link_libraries(GameDevelopmentProject Engine)` call handles it.
