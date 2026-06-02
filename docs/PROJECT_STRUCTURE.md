## Project structure

```
praHangine/
├── CMakeLists.txt          # root build config
├── external/
│   ├── glfw/               # window and input (submodule)
│   └── googletest/         # unit testing (submodule)
├── include/
│   └── prahangine/         # public engine headers
│       ├── core/
│       ├── input/
│       ├── math/
│       ├── pr4/            # file format .PR4 
│       └── render/
├── src/                    # engine implementation
│   ├── core/
│   ├── input/
│   ├── math/
│   ├── pr4/
│   └── render/
├── app/                    # application using the engine
│   └── main.cpp
└── tests/                  # GoogleTest unit tests
```