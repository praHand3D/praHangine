# .PR4 File Format Specification

Binary format for storing 3D scene data in the praHangine engine.

## File Structure

```
[magic: 4 bytes]         PR4 in ASCII (0x50 0x52 0x34 0x34)
[version: 1 byte]        format version, currently 1
[mesh_count: 1 byte]     number of meshes
[object_count: 1 byte]   number of objects
[animation_count: 1 byte] number of animations
[meshes...]
[objects...]
[animations...]
```

## Mesh

```
[mesh_id: 1 byte]
[vertex_count: 2 bytes]
[index_count: 2 bytes]
[vertices: vertex_count * 12 bytes]
[indices: index_count * 6 bytes]
```

One vertex (12 bytes):
```
[x: 4 bytes float]
[y: 4 bytes float]
[z: 4 bytes float]
```

One index (6 bytes) - one triangle:
```
[v0: 2 bytes]
[v1: 2 bytes]
[v2: 2 bytes]
```

## Object

```
[object_id: 1 byte]
[mesh_ref: 1 byte]       references mesh by mesh_id
[position: 12 bytes]     x, y, z as floats
[rotation: 16 bytes]     quaternion x, y, z, w as floats
[scale: 12 bytes]        x, y, z as floats
```

## Animation

```
[animation_id: 1 byte]
[object_ref: 1 byte]     references object by object_id
[fps: 1 byte]            keyframes per second, constant interval
[keyframe_count: 2 bytes]
[keyframes: keyframe_count * 40 bytes]
```

One keyframe (40 bytes):
```
[position: 12 bytes]     x, y, z as floats
[rotation: 16 bytes]     quaternion x, y, z, w as floats
[scale: 12 bytes]        x, y, z as floats
```

## Design decisions

- No separators between values. Parser knows exact byte size of each type.
- Vertex has no ID. It is identified by its position in the list.
- Mesh, object and animation have IDs because they are referenced by other sections.
- Transform (position, rotation, scale) is stored as raw components, not as a 4x4 matrix. The matrix is built at runtime.
- Rotation is stored as a quaternion to avoid gimbal lock and allow correct interpolation.
- Animation uses fixed fps instead of per-keyframe timestamps. The engine controls playback speed.
- Normals and UVs are out of scope for MVP.