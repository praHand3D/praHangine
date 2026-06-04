# Project Structure

```
praHangine/
├── CMakeLists.txt              # root build config
├── cmake/                      # CMake helper modules
│
├── external/
│   ├── glad/                   # OpenGL function loader
│   ├── glfw/                   # window and input (submodule)
│   └── googletest/             # unit testing (submodule)
│
├── include/
│   └── prahangine/             # public engine headers
│       ├── input/              # input callbacks
│       ├── math/               # Vec, Transform, Matrix4x4
│       ├── pr4/                # .PR4 format: types, errors, AssetSystem
│       ├── render/             # Renderer, shader loader
│       └── scene/              # SceneObject
│
├── src/                        # engine implementation
│   ├── input/
│   ├── math/                   # Matrix operations
│   ├── pr4/                    # AssetSystem load/write
│   ├── render/                 # Renderer, shaders
│   └── utils/                  # helpers (createCube, etc.)
│
├── app/                        # application
│   ├── App.h / App.cpp         # App class: init, run, initWindow, initScene
│   ├── main.cpp                # entry point
│   ├── sandbox.cpp             # scratch/playground (separate target)
│   └── shaders/                # GLSL vertex and fragment shaders
│
├── data/                       # .PR4 asset files
│   └── test/                   # test assets
│
├── docs/                       # documentation
│   ├── PROJECT_STRUCTURE.md
│   └── PR4_FORMAT.md
│
└── tests/                      # GoogleTest unit tests
    ├── assets/                 # PR4 load/write tests
    └── math/                   # Matrix tests
```

## Module responsibilities

**math/** - Vec3, Vec4, Transform, Matrix4x4. Builds model matrix from Transform (position, rotation, scale).

**pr4/** - Binary .PR4 file format. AssetSystem loads and writes meshes, objects and animations.

**scene/** - SceneObject combines a loaded Object and Mesh with a computed model matrix.

**render/** - Renderer class handles OpenGL setup (shaders, VAO/VBO upload) and per-frame draw calls.

**input/** - GLFW input callbacks.

**app/** - App class wires everything together: window, renderer, asset loading, main loop.
