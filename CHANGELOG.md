# Changelog praHangine

## [Unreleased]

## [1.0.0] - 2026-06-05
### Added
First working 3D engine with OpenGL rendering and keyframe animation playback.

- `App` class - main loop with `initWindow`, `initScene`, `initCamera`, `update(deltaTime)`
- `Renderer` class - mesh upload to GPU (VAO/VBO/EBO), shader compilation, draw call with MVP uniforms
- `Camera` class - LookAt view matrix, perspective projection
- `SceneObject` - scene entity binding mesh, object transform, and optional animation
- `SceneAnimation` - fps-based keyframe playback with speed control and restart
- Vertex and fragment GLSL shaders
- OpenGL Core Profile 3.3 via GLAD + GLFW
- [praMath](https://github.com/praHand3D/praMath) and [praPR4](https://github.com/praHand3D/praPR4) as git submodules


[1.0.0]: https://github.com/praHand3D/praHangine/releases/tag/v1.0.0
[Unreleased]: https://github.com/praHand3D/praHangine/compare/v1.0.0...HEAD