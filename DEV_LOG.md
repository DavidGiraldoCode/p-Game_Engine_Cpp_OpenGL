# DEV_LOG — Memory & Correctness Bug Tracker
**Branch:** mesh_and_render_commands
**Review Date:** 2026-02-20
**Status Key:** `[ ]` Open `[⌛]` Need more guidance  `[🚩]` Fixed but needs review `[✅]` Fixed

---

## CRITICAL — Crashes / Undefined Behaviour

### BUG-01 · Material::SetShaderProgram — Deletes Pointer It Just Stored
- **File:** `engine/source/render/Material.cpp`
- **Status:** `[✅]`
- **What:** Assigns incoming pointer to `m_shaderProgram`, then immediately `delete`s it. Every subsequent call to `Bind()` dereferences freed memory. Also, `shaderProgram = nullptr` only nulls the local parameter, not the member.
- **Fix:** Remove the two lines `delete shaderProgram;` and `shaderProgram = nullptr;`.

---

### BUG-02 · RenderQueue::~RenderQueue — `delete[]` on a Stack Array
- **File:** `engine/source/render/RenderQueue.cpp`
- **Status:** `[✅]`
- **What:** `m_renderCommands` is a fixed-size array declared inside the class (stack memory). Calling `delete[]` on it is undefined behaviour.
- **Fix:** Remove the destructor body entirely. The queue does not own Mesh or Material, so nothing inside the array needs to be freed.

---

### BUG-03 · RenderQueue::Submit — Stores Address of a Local Variable
- **Files:** `engine/source/render/RenderQueue.cpp`, `source/Game.cpp`
- **Status:** `[✅]`
- **What:** `Game::Update()` creates `RenderCommand command` on the stack and passes `&command` to `Submit()`. The instant `Update()` returns, `command` is destroyed. `Engine::Run()` then calls `Draw()` and dereferences that dead address — use-after-free crash.
- **Fix:** Change `m_renderCommands` to store `RenderCommand` values (not pointers). Add a count member. `Submit` takes by value; `Draw` iterates up to count and resets it to 0.

---

### BUG-04 · VertexLayout — Rule of Three Violation (Shallow Copy → Dangling Pointer)
- **Files:** `engine/source/graphics/VertexLayout.h`, `engine/source/render/Mesh.cpp`
- **Status:** `[✅]`
- **What:** `VertexLayout` has a destructor (`delete[] elements`) but no copy constructor or copy assignment operator. The compiler generates shallow copies. In `Game::Init()`, `vertexLayout` is copied into `Mesh` shallowly; when `Init()` ends, `vertexLayout` destructs and deletes the shared array — leaving `m_mesh->m_vertexLayout.elements` dangling.
- **Fix:** Add a deep copy constructor and deep copy assignment operator to `VertexLayout` that allocate a new `elements` array and copy all elements individually.

---

## HIGH — Memory / GPU Leaks

### BUG-05 · Mesh — No Destructor, GPU Resources Never Released
- **File:** `engine/source/render/Mesh.h` / `Mesh.cpp`
- **Status:** `[✅]`
- **What:** `Mesh` creates VAO, VBO, and EBO but never calls `glDeleteVertexArrays` / `glDeleteBuffers`. GPU memory leaks on destruction.
- **Fix:** Add `~Mesh()` that calls `glDeleteVertexArrays(1, &m_VAO)`, `glDeleteBuffers(1, &m_VBO)`, and `glDeleteBuffers(1, &m_EBO)` (guard EBO with `if (m_EBO != 0)`).

---

### BUG-06 · Material — Destructor Commented Out
- **File:** `engine/source/render/Material.cpp`
- **Status:** `[✅]`
- **What:** The destructor that frees `m_shaderProgram` is commented out. `m_shaderProgram` is never deleted.
- **Fix:** Uncomment `~Material()`, declare it in `Material.h`.

---

### BUG-07 · Game::Destroy() — `m_mesh` Never Deleted
- **File:** `source/Game.cpp`
- **Status:** `[✅]`
- **What:** `m_mesh` is heap-allocated with `new` in `Init()`. `Destroy()` is empty. Memory leaked on shutdown.
- **Fix:** Add `delete m_mesh; m_mesh = nullptr;` inside `Game::Destroy()`.

---

### BUG-08 · GraphicsAPI — `&vertices` / `&indices` Passes Wrong Pointer to GPU
- **File:** `engine/source/graphics/GraphicsAPI.cpp` — `CreateVertexBuffer()` and `CreateIndexBuffer()`
- **Status:** `[✅]`
- **What:** `vertices` is a `const float*`. `&vertices` is a `const float**` — the address of the local stack parameter. The GPU receives the address of a stack variable, not the actual geometry data.
- **Fix:** Change `&vertices` → `vertices` and `&indices` → `indices`.

---

## MEDIUM

### BUG-09 · GraphicsAPI::CreateShaderProgram — GPU Handle Leak on Error Paths
- **File:** `engine/source/graphics/GraphicsAPI.cpp`
- **Status:** `[✅]`
- **What:** `vertexShader`, `fragmentShader`, and `shaderProgramID` are all allocated before any compilation checks. Early `return nullptr` paths skip `glDeleteShader` / `glDeleteProgram`, leaking GPU handles.
- **Fix:** Call `glDeleteShader(vertexShader); glDeleteShader(fragmentShader); glDeleteProgram(shaderProgramID);` before each early `return nullptr`.

---

### BUG-10 · Game::m_mesh — Uninitialized Pointer
- **File:** `source/Game.h`
- **Status:** `[✅]`
- **What:** `eng::Mesh* m_mesh;` has no initializer. If `Init()` returns early before reaching `m_mesh = new ...`, the pointer holds garbage.
- **Fix:** Change declaration to `eng::Mesh* m_mesh = nullptr;`.

---

## LOW

### BUG-11 · Mesh — Offset Cast Truncates on 64-bit
- **File:** `engine/source/render/Mesh.cpp`
- **Status:** `[✅]`
- **What:** `(void*)(uint32_t)layout.elements[i].offset` casts through a 4-byte integer before converting to an 8-byte pointer.
- **Fix:** Use `(void*)(uintptr_t)layout.elements[i].offset`.

---

### BUG-12 · RenderQueue::Submit — Silent Drop When Full
- **File:** `engine/source/render/RenderQueue.cpp`
- **Status:** `[✅]`
- **What:** When all 100 slots are used, `Submit()` silently discards the command with no error.
- **Fix:** Add `std::cerr << "ERROR: RenderQueue full, command dropped\n";` (or an assert) when count reaches the limit.

---

### BUG-13 · VertexLayout.h — Missing `#include <GL/glew.h>`
- **File:** `engine/source/graphics/VertexLayout.h`
- **Status:** `[✅]`
- **What:** Uses `GLuint` without including the header that defines it. Works by accident due to include order.
- **Fix:** Add `#include <GL/glew.h>` at the top of `VertexLayout.h`.

---

## Summary

| ID | Severity | File | Issue |
|----|----------|------|-------|
| BUG-01 | Critical | Material.cpp | Delete after assign — dangling pointer |
| BUG-02 | Critical | RenderQueue.cpp | `delete[]` on stack array — UB |
| BUG-03 | Critical | RenderQueue.cpp / Game.cpp | Storing address of local variable |
| BUG-04 | Critical | VertexLayout.h / Mesh.cpp | Rule of Three — shallow copy + dangling |
| BUG-05 | High | Mesh.h / Mesh.cpp | No destructor — GPU resource leak |
| BUG-06 | High | Material.cpp | Destructor commented out — leak |
| BUG-07 | High | Game.cpp | m_mesh never deleted in Destroy() |
| BUG-08 | High | GraphicsAPI.cpp | &vertices double-pointer — corrupt data |
| BUG-09 | Medium | GraphicsAPI.cpp | Shader handle leak on error path |
| BUG-10 | Medium | Game.h | m_mesh uninitialized pointer |
| BUG-11 | Low | Mesh.cpp | Offset cast truncation on 64-bit |
| BUG-12 | Low | RenderQueue.cpp | Silent drop when queue full |
| BUG-13 | Low | VertexLayout.h | Missing GLuint include |
