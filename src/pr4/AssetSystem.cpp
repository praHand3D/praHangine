#include <filesystem>
#include <fstream>
#include "prahangine/pr4/AssetSystem.h"
#include "prahangine/pr4/errors.h"
#include "prahangine/config.h"


PR4_LOAD_ERROR AssetSystem::load(const char* path) {
    if (!std::filesystem::exists(path))
        return PR4_LOAD_ERROR::FILE_NOT_FOUND;

    if (std::filesystem::path(path).extension() != ".PR4")
        return PR4_LOAD_ERROR::INVALID_EXTENSION;

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
        return PR4_LOAD_ERROR::CANT_OPEN;

    // ---- LOAD HEADER ----
    if (!file.read(reinterpret_cast<char*>(this->header.magic), 4))
        return PR4_LOAD_ERROR::SOMETHING_WRONG;

    if (std::memcmp(this->header.magic, PR4_MAGIC,4) != 0)
        return PR4_LOAD_ERROR::INVALID_MAGIC;

    if (!file.read(reinterpret_cast<char*>(&this->header.version), 1))
        return PR4_LOAD_ERROR::SOMETHING_WRONG;

    if (this->header.version != PR4_VERSION)
        return PR4_LOAD_ERROR::INVALID_VERSION;

    if (!file.read(reinterpret_cast<char*>(&this->header.mesh_count), 1) ||
        !file.read(reinterpret_cast<char*>(&this->header.object_count), 1) ||
        !file.read(reinterpret_cast<char*>(&this->header.animation_count), 1))
        return PR4_LOAD_ERROR::SOMETHING_WRONG;


    // ---- LOAD DATA ----
    for (int8_t i=0; i<this->header.mesh_count; i++) {
        Mesh mesh = Mesh();

        if (!file.read(reinterpret_cast<char*>(&mesh.id), 1))
            return PR4_LOAD_ERROR::SOMETHING_WRONG;

        uint16_t vertex_count = 0;
        uint16_t index_count = 0;

        if (!file.read(reinterpret_cast<char*>(&vertex_count), 2) ||
            !file.read(reinterpret_cast<char*>(&index_count), 2))
            return PR4_LOAD_ERROR::SOMETHING_WRONG;

        for (uint16_t v=0; v<vertex_count; v++) {
            Vertex vertex = Vertex();
            if (!file.read(reinterpret_cast<char*>(&vertex.position), 12))
                return PR4_LOAD_ERROR::SOMETHING_WRONG;
            mesh.vertexes.push_back(vertex);
        }

        for (uint16_t in=0; in<index_count; in++) {
            Index index = Index();
            if (!file.read(reinterpret_cast<char*>(&index.vertexes_index), 6))
                return PR4_LOAD_ERROR::SOMETHING_WRONG;
            mesh.indices.push_back(index);
        }

        this->meshes.push_back(mesh);
    }

    for (int8_t i=0; i<this->header.object_count; i++) {
        Object object = Object();

        if (!file.read(reinterpret_cast<char*>(&object.id), 1) ||
            !file.read(reinterpret_cast<char*>(&object.mesh_ref), 1) ||
            !file.read(reinterpret_cast<char*>(&object.position), 12) ||
            !file.read(reinterpret_cast<char*>(&object.rotation), 16) ||
            !file.read(reinterpret_cast<char*>(&object.scale),  12))
            return PR4_LOAD_ERROR::SOMETHING_WRONG;

        this->objects.push_back(object);
    }

    for (int8_t i=0; i<this->header.animation_count; i++) {
        Animation animation = Animation();

        if (!file.read(reinterpret_cast<char*>(&animation.id), 1) ||
            !file.read(reinterpret_cast<char*>(&animation.object_ref), 1) ||
            !file.read(reinterpret_cast<char*>(&animation.fps), 1))
            return PR4_LOAD_ERROR::SOMETHING_WRONG;

        uint16_t keyframe_count = 0;

        if (!file.read(reinterpret_cast<char*>(&keyframe_count), 2))
            return PR4_LOAD_ERROR::SOMETHING_WRONG;

        for (uint16_t k=0; k<keyframe_count; k++) {
            Keyframe keyframe = Keyframe();

            if (!file.read(reinterpret_cast<char*>(&keyframe.position), 12) ||
                !file.read(reinterpret_cast<char*>(&keyframe.rotation), 16) ||
                !file.read(reinterpret_cast<char*>(&keyframe.scale), 12))
                    return PR4_LOAD_ERROR::SOMETHING_WRONG;

            animation.keyframes.push_back(keyframe);
        }

        this->animations.push_back(animation);
    }

    file.close();

    return PR4_LOAD_ERROR::OK;
}

PR4_WRITER_ERROR AssetSystem::write(const char *path) {
    if (std::filesystem::path(path).extension() != ".PR4")
        return PR4_WRITER_ERROR::INVALID_EXTENSION;

    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(std::filesystem::path(path).parent_path());

    std::ofstream file(path, std::ios::binary);
    if (!file.is_open())
        return PR4_WRITER_ERROR::CANT_OPEN;

    // ---- WRITE HEADER ----
    if (!file.write(reinterpret_cast<const char*>(PR4_MAGIC), 4) ||
        !file.write(reinterpret_cast<const char*>(&PR4_VERSION), 1) ||
        !file.write(reinterpret_cast<const char*>(&this->header.mesh_count), 1) ||
        !file.write(reinterpret_cast<const char*>(&this->header.object_count), 1) ||
        !file.write(reinterpret_cast<const char*>(&this->header.animation_count), 1))
        return PR4_WRITER_ERROR::SOMETHING_WRONG;

    // ---- WRITE DATA ----
    for (int8_t i=0; i<this->header.mesh_count; i++) {
        const Mesh& mesh = this->meshes[i];
        uint16_t vertex_count = mesh.vertexes.size();
        uint16_t index_count = mesh.indices.size();

        if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&mesh.id), 1) ||
            !file.write(reinterpret_cast<char*>(&vertex_count), 2) ||
            !file.write(reinterpret_cast<char*>(&index_count), 2))
            return PR4_WRITER_ERROR::SOMETHING_WRONG;


        for (uint16_t v=0; v<vertex_count; v++)
            if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&mesh.vertexes[v].position), 12))
                return PR4_WRITER_ERROR::SOMETHING_WRONG;

        for (uint16_t in=0; in<index_count; in++)
            if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&mesh.indices[in].vertexes_index), 6))
                return PR4_WRITER_ERROR::SOMETHING_WRONG;
    }

    for (int8_t i=0; i<this->header.object_count; i++) {
        const Object& object = this->objects[i];

        if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&object.id), 1) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&object.mesh_ref), 1) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&object.position), 12) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&object.rotation), 16) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&object.scale), 12))
            return PR4_WRITER_ERROR::SOMETHING_WRONG;
    }

    for (uint8_t i=0; i<this->header.animation_count; i++) {
        const Animation& animation = this->animations[i];
        uint16_t keyframe_count = animation.keyframes.size();

        if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.id), 1) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.object_ref), 1) ||
            !file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.fps), 1) ||
            !file.write(reinterpret_cast<char*>(&keyframe_count), 2))
            return PR4_WRITER_ERROR::SOMETHING_WRONG;

        for (uint16_t k=0; k<keyframe_count; k++)
            if (!file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.keyframes[k].position), 12) ||
                !file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.keyframes[k].rotation), 16) ||
                !file.write(reinterpret_cast<const std::ostream::char_type *>(&animation.keyframes[k].scale), 12))
                return PR4_WRITER_ERROR::SOMETHING_WRONG;
    }

    file.close();

    return PR4_WRITER_ERROR::OK;
}
