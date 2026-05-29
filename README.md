# praHangine

Custom 3D engine written in C++ from scratch. Part of the praHand3D project - a hand motion monitoring system that visualizes sensor data from a glove in real time.

## Requirements

- CMake 3.20+
- C++20 compiler (clang or gcc)
- Git

## Building

Clone with submodules:

```bash
git clone --recurse-submodules <repo-url>
cd praHangine
```

Build with CMake:

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

Run the app:

```bash
./cmake-build-debug/bin/app
```

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
│       └── render/
├── src/                    # engine implementation
│   ├── core/
│   ├── input/
│   ├── math/
│   └── render/
├── app/                    # application using the engine
│   └── main.cpp
└── tests/                  # GoogleTest unit tests
```

## Dependencies

| Library | Version | Purpose |
|---|---|---|
| GLFW | 3.x | window creation, input handling |
| GoogleTest | latest | unit testing |

Both are included as git submodules — no manual installation needed.
